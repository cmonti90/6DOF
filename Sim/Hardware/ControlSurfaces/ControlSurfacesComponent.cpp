
#include "ControlSurfacesComponent.h"
#include "ControlSurfacesTypes.h"

#include "ControlSurfaces.h"

ControlSurfacesComponent::ControlSurfacesComponent( std::shared_ptr<PubSub::QueueMngr> queueMngr, const PubSub::Component_Label name )
    : PubSub::SimComponent( queueMngr, 1000, name ),
    pAlg( new CtrlSurfs() ),
    inData_( new CtrlSurfTypes::InData() ),
    outData_( new CtrlSurfTypes::OutData() ),
    counter_( 0u )
{
}

ControlSurfacesComponent::~ControlSurfacesComponent()
{
}

void ControlSurfacesComponent::initialize( void )
{
    inData_->initialize();
    outData_->initialize();

    subscribe<AutopilotMsg>(*inData_);

    pAlg->initialize();
    counter_ = 0u;
}

void ControlSurfacesComponent::update( void )
{

    PubSub::Message_Label label;
    PubSub::MessageStatus status = peek( label );

    while (status == PubSub::MessageStatus::MESSAGE_AVAILABLE)
    {
        switch (label)
        {
        case AutopilotMsg::MESSAGE_LABEL:
            receive<AutopilotMsg>(*inData_ );
            break;

        default:
            removeTopMessage();
            break;
        }

        status = peek( label );
    }

    pAlg->exec(*inData_, *outData_);

    send<CtrlSurfMsg>(*outData_);

    counter_++;
}

void ControlSurfacesComponent::finalize( void )
{
    pAlg->finalize();
}