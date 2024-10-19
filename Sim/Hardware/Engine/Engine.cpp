#include "Engine.h"
#include "EngineTypes.h"
#include "PhysicalProperties.h"

#include "ForceEffector.h"

#include <math.h>

#include <iostream>

Engine::Engine( const double runRate, const std::string str )
    : SimLib::HwIntf( runRate, str )
    , endpoint_()
    , swInData_( new EngineTypes::InData() )
    , netForceBody_( 0.0 )
    , netMomentBody_( 0.0 )
    , counter_( 0u )
{
}

Engine::~Engine()
{
}

void Engine::requestReferences( SimLib::ReferenceRequest& refReq )
{
    refReq.requestReference( reinterpret_cast< SimLib::Model** >( &pForceEffector_ ), "ForceEffector" );
}

void Engine::receiveQueueMngr( std::shared_ptr< PubSub::QueueMngr >& queueMngr )
{
    endpoint_.configure( queueMngr );
}

void Engine::initialize()
{
    counter_ = 0u;

    endpoint_.subscribe< HighRateAutopilotMsg >( *swInData_ );
}

void Engine::update()
{
    CheckForMessages();

    netForceBody_  = 0.0;
    netMomentBody_ = 0.0;

    counter_++;
}

void Engine::finalize()
{
}

void Engine::CheckForMessages()
{
    PubSub::Message_Label label;
    PubSub::MessageStatus status = endpoint_.peek( label );

    while ( status == PubSub::MessageStatus::MESSAGE_AVAILABLE )
    {
        switch ( label )
        {
            case HighRateAutopilotMsg::MESSAGE_LABEL:

                endpoint_.receive< HighRateAutopilotMsg >( *swInData_ );

                break;

            default:

                endpoint_.removeTopMessage();

                break;
        }

        status = endpoint_.peek( label );
    }
}