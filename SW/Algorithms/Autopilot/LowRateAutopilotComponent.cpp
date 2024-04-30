
#include "LowRateAutopilotComponent.h"
#include "LowRateAutopilotTypes.h"
#include "LowRateAutopilotAlgorithm.h"
#include "RtcClock.h"
#include "TryCatch.h"

LowRateAutopilotComponent::LowRateAutopilotComponent( std::shared_ptr<PubSub::QueueMngr>& queueMngr,
                                        const std::shared_ptr<TimePt::RtcClock>& sysClock,
                                        const PubSub::Component_Label name )
    : PubSub::Component ( queueMngr, name )
    , endpoint_         ( queueMngr )
    , pAlg_              ( new LowRateAutopilotAlgorithm() )
    , inData_           ( new LowRateAutopilotTypes::InData() )
    , outData_          ( new LowRateAutopilotTypes::OutData() )
    , sysClock_         ( sysClock )
{
}

LowRateAutopilotComponent::~LowRateAutopilotComponent()
{
}

//////////////////////////////////////////////////////
/// @note   Name: associateEvent
/// @brief  Associate event to active component
/// @param  None
/// @return None
//////////////////////////////////////////////////////
bool LowRateAutopilotComponent::associateEvent() const
{
    return endpoint_.hasActiveMessage();
}

void LowRateAutopilotComponent::initialize( void )
{
    BEGIN_CHECKED_EXCEPTION()
    {
        endpoint_.setActiveDepth( active_endpoint_depth );
        endpoint_.setPassiveDepth( passive_endpoint_depth );

        endpoint_.subscribe< GuidanceMsg >( *inData_, PubSub::Message_Type::ACTIVE );

        endpoint_.subscribe< NavMsg      >( *inData_, PubSub::Message_Type::PASSIVE );
    }
    END_CHECKED_EXCEPTION()
}

void LowRateAutopilotComponent::update( void )
{
    BEGIN_CHECKED_EXCEPTION()
    {
        PubSub::Message_Label label;
        PubSub::MessageStatus status = endpoint_.peek( label );

        while ( status == PubSub::MessageStatus::MESSAGE_AVAILABLE )
        {
            switch ( label )
            {
                case GuidanceMsg::MESSAGE_LABEL:

                    endpoint_.receive< GuidanceMsg >( *inData_ );

                    break;

                case NavMsg::MESSAGE_LABEL:

                    endpoint_.receive< NavMsg >( *inData_ );

                    break;

                default:

                    endpoint_.removeTopMessage();

                    break;
            }

            endpoint_.send< LowRateAutopilotMsg >( *outData_ );

            status = endpoint_.peek( label );
        }
    }
    END_CHECKED_EXCEPTION()
}

void LowRateAutopilotComponent::finalize( void )
{
    BEGIN_CHECKED_EXCEPTION()
    {
        pAlg_->finalize();
    }
    END_CHECKED_EXCEPTION()
}