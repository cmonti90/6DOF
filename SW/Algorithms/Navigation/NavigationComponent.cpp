
#include "NavigationComponent.h"
#include "NavigationTypes.h"
#include "NavigationAlgorithm.h"

NavigationComponent::NavigationComponent( std::shared_ptr<PubSub::QueueMngr> queueMngr, const PubSub::COMPONENT_LABEL name )
    : PubSub::Component( queueMngr, name ), pAlg( new NavigationAlgorithm() ), inData_( new NavTypes::InData() ), outData_( new NavTypes::OutData() )
{
}

NavigationComponent::~NavigationComponent()
{
}

void NavigationComponent::initialize( void )
{
    // subscribe( test1Msg_.get(), PubSub::Message_Type::ACTIVE );

    // pAlg->initialize();
}

void NavigationComponent::update( void )
{
    PubSub::Message_Label label;
    PubSub::MessageStatus status = peek( label );

    while (status == PubSub::MessageStatus::MESSAGE_AVAILABLE)
    {
        switch (label)
        {
        // case test1Msg::MESSAGE_LABEL:
        //     receive( test1Msg_.get() );

        //     test2Msg_->msg2data += 0.1;

        //     send( test2Msg_.get() );
        //     break;

        default:
            removeTopMessage();
            break;
        }

        status = peek( label );
    }
}

void NavigationComponent::finalize( void )
{
    pAlg->finalize();
}