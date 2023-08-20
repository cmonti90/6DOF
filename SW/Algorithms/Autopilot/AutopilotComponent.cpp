
#include "AutopilotComponent.h"
#include "AutopilotTypes.h"
#include "AutopilotAlgorithm.h"

#include <iostream>

AutopilotComponent::AutopilotComponent(std::shared_ptr<PubSub::QueueMngr> queueMngr, const PubSub::COMPONENT_LABEL name)
: PubSub::Component(queueMngr, name), pAlg(new AutopilotAlgorithm()), inData_(new AutopilotTypes::InData()), outData_(new AutopilotTypes::OutData())
{
}

AutopilotComponent::~AutopilotComponent()
{
}

void AutopilotComponent::initialize(void)
{
    // subscribe(test1Msg_.get(), PubSub::Message_Type::ACTIVE);

    // pAlg->initialize();
}

void AutopilotComponent::update(void)
{
    PubSub::Message_Label label;
    PubSub::MessageStatus status = peek(label);

    while (status == PubSub::MessageStatus::MESSAGE_AVAILABLE)
    {
        switch (label)
        {
            // case test1Msg::MESSAGE_LABEL:
            //     receive(test1Msg_.get());

            //     test2Msg_->msg2data += 0.1;

            //     send(test2Msg_.get());
            //     break;

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