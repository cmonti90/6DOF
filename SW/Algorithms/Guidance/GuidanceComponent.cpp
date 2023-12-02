
#include "GuidanceComponent.h"
#include "GuidanceTypes.h"
#include "GuidanceAlgorithm.h"
#include "RtcClock.h"
#include "TryCatch.h"

#include <iostream>


//////////////////////////////////////////////////////
/// @note   Name: Constructor
/// @brief  Constructor
/// @param  Queue manager
/// @param  System clock
/// @param  Component name
/// @return None
//////////////////////////////////////////////////////
GuidanceComponent::GuidanceComponent( std::shared_ptr<PubSub::QueueMngr>& queueMngr,
                                      const std::shared_ptr<TimePt::RtcClock>& sysClock,
                                      const PubSub::Component_Label name )
    : PubSub::Component ( queueMngr, name )
    , pAlg              ( new GuidanceAlgorithm() )
    , inData_           ( new GuidanceTypes::InData() )
    , outData_          ( new GuidanceTypes::OutData() )
    , sysClock_         ( sysClock )
{
}


//////////////////////////////////////////////////////
/// @note   Name: Destructor
/// @brief  Destructor
/// @param  None
/// @return None
//////////////////////////////////////////////////////
GuidanceComponent::~GuidanceComponent()
{
}


//////////////////////////////////////////////////////
/// @note   Name: initialize
/// @brief  initialize data structures, algorithms, and
///         subscribe to messages
/// @param  None
/// @return None
//////////////////////////////////////////////////////
void GuidanceComponent::initialize( void )
{
    BEGIN_CHECKED_EXCEPTION()
    {
        inData_ ->initialize();
        outData_->initialize();

        subscribe< NavMsg >( *inData_, PubSub::Message_Type::ACTIVE );

        pAlg->initialize();
    }
    END_CHECKED_EXCEPTION()
}


//////////////////////////////////////////////////////
/// @note   Name: update
/// @brief  Receive messages, execute algorithms
///         and send messages. Runs when component
///         receives an active message
/// @param  None
/// @return None
//////////////////////////////////////////////////////
void GuidanceComponent::update( void )
{
    BEGIN_CHECKED_EXCEPTION()
    {
        inData_->reset();

        PubSub::Message_Label label;
        PubSub::MessageStatus status = peek( label );

        while ( status == PubSub::MessageStatus::MESSAGE_AVAILABLE )
        {
            switch ( label )
            {
                case NavMsg::MESSAGE_LABEL:

                    receive< NavMsg >( *inData_ );

                    break;

                default:

                    removeTopMessage();
                    break;
            }

            status = peek( label );
        }
    }
    END_CHECKED_EXCEPTION()
}


//////////////////////////////////////////////////////
/// @note   Name: finalize
/// @brief  Runs at simulation end
/// @param  None
/// @return None
//////////////////////////////////////////////////////
void GuidanceComponent::finalize( void )
{
    BEGIN_CHECKED_EXCEPTION()
    {
        pAlg->finalize();
    }
    END_CHECKED_EXCEPTION()
}