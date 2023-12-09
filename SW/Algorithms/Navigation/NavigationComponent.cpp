
#include "NavigationComponent.h"
#include "NavigationTypes.h"
#include "NavigationAlgorithm.h"
#include "RtcClock.h"
#include "TryCatch.h"

#include <iostream>

NavigationComponent::NavigationComponent(
    std::shared_ptr<PubSub::QueueMngr>& queueMngr,
    const std::shared_ptr<TimePt::RtcClock>& sysClock,
    const PubSub::Component_Label name )
    : PubSub::Component ( queueMngr, name )
    , endpoint_         ( queueMngr )
    , pAlg              ( new NavigationAlgorithm() )
    , inData_           ( new NavTypes::InData() )
    , outData_          ( new NavTypes::OutData() )
    , sysClock_         ( sysClock )
    , counter_          ( 0 )
{
}

NavigationComponent::~NavigationComponent()
{
}


//////////////////////////////////////////////////////
/// @note   Name: associateEvent
/// @brief  Associate event to active component
/// @param  None
/// @return None
//////////////////////////////////////////////////////
bool NavigationComponent::associateEvent() const
{
    return endpoint_.hasActiveMessage();
}

void NavigationComponent::initialize( void )
{
    inData_->initialize();
    outData_->initialize();

    endpoint_.subscribe< ImuMsg >( *inData_, PubSub::Message_Type::ACTIVE );

    pAlg->initialize();

    counter_ = 0;
}

void NavigationComponent::update( void )
{
    BEGIN_CHECKED_EXCEPTION()
    {
        PubSub::Message_Label label;
        PubSub::MessageStatus status = endpoint_.peek( label );

        while ( status == PubSub::MessageStatus::MESSAGE_AVAILABLE )
        {
            switch ( label )
            {
                case ImuMsg::MESSAGE_LABEL:
                
                    endpoint_.receive< ImuMsg >( *inData_ );

                    break;

                default:

                    endpoint_.removeTopMessage();

                    break;
            }

            status = endpoint_.peek( label );
        }

        outData_->accEcef = static_cast< double >( counter_ ) * myMath::Vector3d( {1.0, -2.0, 1.5} );

        endpoint_.send< NavMsg >( *outData_ );

        counter_++;
    }
    END_CHECKED_EXCEPTION()
}

void NavigationComponent::finalize( void )
{
    pAlg->finalize();
}