
#include "AutopilotComponent.h"
#include "AutopilotTypes.h"
#include "AutopilotAlgorithm.h"

AutopilotComponent::AutopilotComponent(std::shared_ptr<PubSub::QueueMngr> queueMngr, const PubSub::COMPONENT_LABEL name)
    : PubSub::Component(queueMngr, name),
      pAlg(new AutopilotAlgorithm()),
      inData_(new AutopilotTypes::InData()),
      outData_(new AutopilotTypes::OutData())
{
}

AutopilotComponent::~AutopilotComponent()
{
}

void AutopilotComponent::initialize(void)
{
    subscribe<GuidanceMsg>(*inData_, PubSub::Message_Type::ACTIVE);

    subscribe<NavMsg>(*inData_, PubSub::Message_Type::PASSIVE);

    pAlg->initialize();
}

void AutopilotComponent::update(void)
{
    PubSub::Message_Label label;
    PubSub::MessageStatus status = peek(label);

    while (status == PubSub::MessageStatus::MESSAGE_AVAILABLE)
    {
        switch (label)
        {
        case GuidanceMsg::MESSAGE_LABEL:
            receive<GuidanceMsg>(*inData_);

            break;

        case NavMsg::MESSAGE_LABEL:
            receive<NavMsg>(*inData_);

            break;

        default:
            removeTopMessage();
            break;
        }

        status = peek(label);
    }
}

void AutopilotComponent::finalize(void)
{
    pAlg->finalize();
}