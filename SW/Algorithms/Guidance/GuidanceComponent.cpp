
#include "GuidanceComponent.h"
#include "GuidanceTypes.h"
#include "GuidanceAlgorithm.h"

#include <iostream>

GuidanceComponent::GuidanceComponent( std::shared_ptr<PubSub::QueueMngr> queueMngr, const PubSub::COMPONENT_LABEL name )
    : PubSub::Component( queueMngr, name ), pAlg( new GuidanceAlgorithm() ), inData_( new GuidanceTypes::InData() ), outData_( new GuidanceTypes::OutData() )
{
}

GuidanceComponent::~GuidanceComponent()
{
}

void GuidanceComponent::initialize( void )
{

    // subscribe( test1Msg_.get(), PubSub::Message_Type::ACTIVE );

    // pAlg->initialize();
}

void GuidanceComponent::update( void )
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

void GuidanceComponent::finalize( void )
{
    pAlg->finalize();
}