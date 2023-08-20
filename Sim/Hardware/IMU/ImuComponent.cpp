
#include "ImuComponent.h"
#include "ImuTypes.h"

#include "Imu.h"

ImuComponent::ImuComponent( std::shared_ptr<PubSub::QueueMngr> queueMngr, const PubSub::COMPONENT_LABEL name )
    : PubSub::SimComponent( queueMngr, 1000, name ),
    pAlg( new Imu() ),
    inData_( new ImuTypes::InData() ),
    outData_( new ImuTypes::OutData() ),
    counter_( 0u )
{
}

ImuComponent::~ImuComponent()
{
}

void ImuComponent::initialize( void )
{

    subscribe<EomMsg>(*inData_);

    pAlg->initialize();
    counter_ = 0u;
}

void ImuComponent::update( void )
{

    PubSub::Message_Label label;
    PubSub::MessageStatus status = peek( label );

    while (status == PubSub::MessageStatus::MESSAGE_AVAILABLE)
    {
        switch (label)
        {
        case EomMsg::MESSAGE_LABEL:
            receive<EomMsg>(*inData_);
            break;

        default:
            removeTopMessage();
            break;
        }

        status = peek( label );
    }

    // pAlg->exec();

    send<ImuMsg>(*outData_);

    counter_++;
}

void ImuComponent::finalize( void )
{
    pAlg->finalize();
}