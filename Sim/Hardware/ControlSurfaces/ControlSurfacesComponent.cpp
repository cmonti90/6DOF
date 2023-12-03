
#include "ControlSurfacesComponent.h"
#include "ControlSurfacesTypes.h"

#include "ControlSurfaces.h"

ControlSurfacesComponent::ControlSurfacesComponent(
    std::shared_ptr<PubSub::QueueMngr>& queueMngr,
    const std::shared_ptr<TimePt::RtcClock>& sysClock,
    const PubSub::Component_Label name )
    : PubSub::SimComponent  ( queueMngr, 1000, name )
    , endpoint_             ( queueMngr )
    , pAlg                  ( new CtrlSurfs() )
    , inData_               ( new CtrlSurfTypes::InData() )
    , outData_              ( new CtrlSurfTypes::OutData() )
    , sysClock_             ( sysClock )
    , counter_              ( 0u )
{
}

ControlSurfacesComponent::~ControlSurfacesComponent()
{
}

void ControlSurfacesComponent::initialize( void )
{
    inData_->initialize();
    outData_->initialize();

    endpoint_.subscribe< AutopilotMsg >( *inData_ );

    pAlg->initialize();
    counter_ = 0u;
}

void ControlSurfacesComponent::update( void )
{

    PubSub::Message_Label label;
    PubSub::MessageStatus status = endpoint_.peek( label );

    while ( status == PubSub::MessageStatus::MESSAGE_AVAILABLE )
    {
        switch ( label )
        {
            case AutopilotMsg::MESSAGE_LABEL:

                endpoint_.receive< AutopilotMsg >( *inData_ );

                break;

            default:

                endpoint_.removeTopMessage();

                break;
        }

        status = endpoint_.peek( label );
    }

    pAlg->exec( *inData_, *outData_ );

    endpoint_.send< CtrlSurfMsg >( *outData_ );

    counter_++;
}

void ControlSurfacesComponent::finalize( void )
{
    pAlg->finalize();
}