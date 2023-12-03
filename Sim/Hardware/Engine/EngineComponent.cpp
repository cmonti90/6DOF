
#include "EngineComponent.h"
#include "EngineTypes.h"

#include "engine.h"

EngineComponent::EngineComponent( std::shared_ptr<PubSub::QueueMngr>& queueMngr, const PubSub::Component_Label name )
    : PubSub::SimComponent( queueMngr, 1000, name )
    , endpoint_ ( queueMngr )
    , pAlg      ( new engine() )
    , inData_   ( new EngineTypes::InData() )
    , outData_  ( new EngineTypes::OutData() )
    , counter_  ( 0u )
{
}

EngineComponent::~EngineComponent()
{
}

void EngineComponent::initialize( void )
{
    inData_ ->initialize();
    outData_->initialize();

    endpoint_.subscribe< AutopilotMsg >( *inData_ );

    pAlg->initialize();
    counter_ = 0u;
}

void EngineComponent::update( void )
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

    endpoint_.send< EngineMsg >( *outData_ );

    counter_++;
}

void EngineComponent::finalize( void )
{
    pAlg->finalize();
}