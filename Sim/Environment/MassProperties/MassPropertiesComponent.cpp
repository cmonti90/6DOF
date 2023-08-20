
#include "MassPropertiesComponent.h"
#include "MassPropertiesTypes.h"

#include "MassProperties.h"

MassPropertiesComponent::MassPropertiesComponent( std::shared_ptr<PubSub::QueueMngr> queueMngr, const PubSub::COMPONENT_LABEL name )
    : PubSub::SimComponent( queueMngr, 1000, name ), pAlg( new MassProperties() ), inData_( new MassPropTypes::InData()), outData_( new MassPropTypes::OutData() ), counter_( 0u )
{
}

MassPropertiesComponent::~MassPropertiesComponent()
{
}

void MassPropertiesComponent::initialize( void )
{

    // subscribe( test2Msg_.get(), PubSub::Message_Type::ACTIVE );

    // pAlg->initialize();
    counter_ = 0u;
}

void MassPropertiesComponent::update( void )
{

    PubSub::Message_Label label;
    PubSub::MessageStatus status = peek( label );

    while (status == PubSub::MessageStatus::MESSAGE_AVAILABLE)
    {
        switch (label)
        {
        // case test2Msg::MESSAGE_LABEL:
        //     receive( test2Msg_.get() );
        //     break;

        default:
            removeTopMessage();
            break;
        }

        status = peek( label );
    }

    // pAlg->exec();

    if (counter_ % 5 == 0)
    {
        // send( test1Msg_.get() );
    }

    counter_++;
}

void MassPropertiesComponent::finalize( void )
{
    pAlg->finalize();
}