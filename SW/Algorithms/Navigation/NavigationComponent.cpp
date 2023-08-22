
#include "NavigationComponent.h"
#include "NavigationTypes.h"
#include "NavigationAlgorithm.h"
#include "TryCatch.h"

NavigationComponent::NavigationComponent(std::shared_ptr<PubSub::QueueMngr> queueMngr,
                                         const std::shared_ptr<TimePt::RtcClock> rtcClock,
                                         const PubSub::COMPONENT_LABEL name)
    : PubSub::Component(queueMngr, name),
      pAlg(new NavigationAlgorithm()),
      inData_(new NavTypes::InData()),
      outData_(new NavTypes::OutData())
{
}

NavigationComponent::~NavigationComponent()
{
}

void NavigationComponent::initialize(void)
{
    inData_->initialize();
    outData_->initialize();
    
    subscribe<ImuMsg>(*inData_, PubSub::Message_Type::ACTIVE);

    pAlg->initialize();
}

void NavigationComponent::update(void)
{
    BEGIN_CHECKED_EXCEPTION()
    {
        PubSub::Message_Label label;
        PubSub::MessageStatus status = peek(label);

        while (status == PubSub::MessageStatus::MESSAGE_AVAILABLE)
        {
            switch (label)
            {
            case ImuMsg::MESSAGE_LABEL:
                receive<ImuMsg>(*inData_);

                break;

            default:
                removeTopMessage();
                break;
            }

            status = peek(label);
        }
    }
    END_CHECKED_EXCEPTION()
}

void NavigationComponent::finalize(void)
{
    pAlg->finalize();
}