
#include "ImuComponent.h"
#include "ImuTypes.h"

#include "Imu.h"

ImuComponent::ImuComponent( std::shared_ptr<PubSub::QueueMngr>& queueMngr,
                            const std::shared_ptr<TimePt::RtcClock>& sysClock,
                            const PubSub::Component_Label name )
    : PubSub::SimComponent  ( queueMngr, 1000, name )
    , endpoint_             ( queueMngr )
    , pAlg                  ( new Imu() )
    , inData_               ( new ImuTypes::InData() )
    , outData_              ( new ImuTypes::OutData() )
    , sysClock_             ( sysClock )
    , counter_              ( 0u )
{
}

ImuComponent::~ImuComponent()
{
}

void ImuComponent::initialize( void )
{
    inData_->initialize();
    outData_->initialize();

    endpoint_.subscribe< EomMsg >( *inData_ );

    pAlg->initialize();
    counter_ = 0u;
}

void ImuComponent::update( void )
{

    PubSub::Message_Label label;
    PubSub::MessageStatus status = endpoint_.peek( label );

    while ( status == PubSub::MessageStatus::MESSAGE_AVAILABLE )
    {
        switch ( label )
        {
            case EomMsg::MESSAGE_LABEL:

                endpoint_.receive< EomMsg >( *inData_ );

                break;

            default:

                endpoint_.removeTopMessage();

                break;
        }

        status = endpoint_.peek( label );
    }

    pAlg->exec( *inData_, *outData_ );

    endpoint_.send< ImuMsg >( *outData_ );

    counter_++;
}

void ImuComponent::finalize( void )
{
    pAlg->finalize();
}