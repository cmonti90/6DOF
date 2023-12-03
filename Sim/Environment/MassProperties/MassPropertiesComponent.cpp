
#include "MassPropertiesComponent.h"
#include "MassPropertiesTypes.h"

#include "MassProperties.h"

MassPropertiesComponent::MassPropertiesComponent( std::shared_ptr<PubSub::QueueMngr>& queueMngr, const PubSub::Component_Label name )
    : PubSub::SimComponent  ( queueMngr, 1000, name )
    , endpoint_             ( queueMngr )
    , pAlg                  ( new MassProperties() )
    , inData_               ( new MassPropTypes::InData() )
    , outData_              ( new MassPropTypes::OutData() )
    , counter_              ( 0u )
{
}

MassPropertiesComponent::~MassPropertiesComponent()
{
}

void MassPropertiesComponent::initialize( void )
{
    inData_->initialize();
    outData_->initialize();

    endpoint_.subscribe< EngineMsg >( *inData_ );

    pAlg->initialize();
    counter_ = 0u;
}

void MassPropertiesComponent::update( void )
{

    PubSub::Message_Label label;
    PubSub::MessageStatus status = endpoint_.peek( label );

    while ( status == PubSub::MessageStatus::MESSAGE_AVAILABLE )
    {
        switch ( label )
        {
            case EngineMsg::MESSAGE_LABEL:
                endpoint_.receive< EngineMsg >( *inData_ );
                break;

            default:
                endpoint_.removeTopMessage();
                break;
        }

        status = endpoint_.peek( label );
    }

    pAlg->exec( *inData_, *outData_ );

    endpoint_.send< MassPropMsg >( *outData_ );

    counter_++;
}

void MassPropertiesComponent::finalize( void )
{
    pAlg->finalize();
}