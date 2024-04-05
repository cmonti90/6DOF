
#include "HighRateAutopilotComponent.h"
#include "HighRateAutopilotTypes.h"
#include "HighRateAutopilotAlgorithm.h"
#include "RtcClock.h"
#include "TryCatch.h"

HighRateAutopilotComponent::HighRateAutopilotComponent( std::shared_ptr<PubSub::QueueMngr>& queueMngr,
        const std::shared_ptr<TimePt::RtcClock>& sysClock,
        const PubSub::Component_Label name )
    : PubSub::Component ( queueMngr, name )
    , endpoint_         ( queueMngr )
    , pAlg              ( new HighRateAutopilotAlgorithm() )
    , inData_           ( new HighRateAutopilotTypes::InData() )
    , outData_          ( new HighRateAutopilotTypes::OutData() )
    , sysClock_         ( sysClock )
{
}

HighRateAutopilotComponent::~HighRateAutopilotComponent()
{
}

//////////////////////////////////////////////////////
/// @note   Name: associateEvent
/// @brief  Associate event to active component
/// @param  None
/// @return None
//////////////////////////////////////////////////////
bool HighRateAutopilotComponent::associateEvent() const
{
    return endpoint_.hasActiveMessage();
}

void HighRateAutopilotComponent::initialize( void )
{
    BEGIN_CHECKED_EXCEPTION()
    {
        inData_ ->initialize();
        outData_->initialize();

        endpoint_.setActiveDepth( active_endpoint_depth );
        endpoint_.setPassiveDepth( passive_endpoint_depth );

        endpoint_.subscribe< GuidanceMsg >( *inData_, PubSub::Message_Type::ACTIVE );

        endpoint_.subscribe< NavMsg      >( *inData_, PubSub::Message_Type::PASSIVE );

        pAlg->initialize();
    }
    END_CHECKED_EXCEPTION()
}

void HighRateAutopilotComponent::update( void )
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

            status = endpoint_.peek( label );
        }
    }
    END_CHECKED_EXCEPTION()
}

void HighRateAutopilotComponent::finalize( void )
{
    BEGIN_CHECKED_EXCEPTION()
    {
        pAlg->finalize();
    }
    END_CHECKED_EXCEPTION()
}