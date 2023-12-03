
#include "AutopilotComponent.h"
#include "AutopilotTypes.h"
#include "AutopilotAlgorithm.h"
#include "RtcClock.h"
#include "TryCatch.h"

AutopilotComponent::AutopilotComponent( std::shared_ptr<PubSub::QueueMngr>& queueMngr,
                                        const std::shared_ptr<TimePt::RtcClock>& sysClock,
                                        const PubSub::Component_Label name )
    : PubSub::Component ( queueMngr, name )
    , endpoint_         ( queueMngr )
    , pAlg              ( new AutopilotAlgorithm() )
    , inData_           ( new AutopilotTypes::InData() )
    , outData_          ( new AutopilotTypes::OutData() )
    , sysClock_         ( sysClock )
{
}

AutopilotComponent::~AutopilotComponent()
{
}

//////////////////////////////////////////////////////
/// @note   Name: associateEvent
/// @brief  Associate event to active component
/// @param  None
/// @return None
//////////////////////////////////////////////////////
bool AutopilotComponent::associateEvent() const
{
    return endpoint_.hasActiveMessage();
}

void AutopilotComponent::initialize( void )
{
    inData_ ->initialize();
    outData_->initialize();

    endpoint_.subscribe< GuidanceMsg >( *inData_, PubSub::Message_Type::ACTIVE );

    endpoint_.subscribe< NavMsg      >( *inData_, PubSub::Message_Type::PASSIVE );

    pAlg->initialize();
}

void AutopilotComponent::update( void )
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

void AutopilotComponent::finalize( void )
{
    pAlg->finalize();
}