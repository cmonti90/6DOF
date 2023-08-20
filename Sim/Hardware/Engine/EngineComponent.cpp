
#include "EngineComponent.h"

#include "engine.h"

EngineComponent::EngineComponent( std::shared_ptr<PubSub::QueueMngr> queueMngr, const PubSub::COMPONENT_LABEL name )
    : PubSub::SimComponent( queueMngr, 1000, name ), pAlg( new engine() ), counter_( 0u )
{
}

EngineComponent::~EngineComponent()
{
}

void EngineComponent::initialize( void )
{

    // subscribe(aeroMsg_.get(), PubSub::Message_Type::ACTIVE);

    pAlg->initialize();
    counter_ = 0u;
}

void EngineComponent::update( void )
{

    PubSub::Message_Label label;
    PubSub::MessageStatus status = peek( label );

    while (status == PubSub::MessageStatus::MESSAGE_AVAILABLE)
    {
        switch (label)
        {
        // case AeroMsg::MESSAGE_LABEL:
        //     receive( aeroMsg_.get() );
        //     break;

        default:
            removeTopMessage();
            break;
        }

        status = peek( label );
    }

    pAlg->exec();

    counter_++;
}

void EngineComponent::finalize( void )
{
    pAlg->finalize();
}