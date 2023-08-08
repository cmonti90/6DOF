
#include "EomComponent.h"

#include "eom.h"

EomComponent::EomComponent(std::shared_ptr<PubSub::QueueMngr> queueMngr, const PubSub::COMPONENT_LABEL name)
    : PubSub::SimComponent(queueMngr, 1000, name), pEom(new eom()), test1Msg_(new test1Msg()), test2Msg_(new test2Msg()), test3Msg_(new test3Msg()), counter_(0u)
{
}

EomComponent::~EomComponent()
{
}

void EomComponent::initialize(void)
{
    std::cout << getComponentLabel() << ": initialize()" << std::endl;

    std::cout << getComponentLabel() << ": subscribing to " << test2Msg_->getMessageLabel() << std::endl;

    subscribe(test2Msg_.get(), PubSub::Message_Type::ACTIVE);

    std::cout << getComponentLabel() << ": subscribed to " << test2Msg_->getMessageLabel() << std::endl;

    counter_ = 0u;
}

void EomComponent::update(void)
{
    std::cout << getComponentLabel() << "::update()" << std::endl;

    PubSub::Message_Label label;
    PubSub::MessageStatus status = peek(label);

    std::cout << getComponentLabel() << " peeked: ";
    std::cout << "status = " << status << ", label = " << label << std::endl;

    while (status == PubSub::MessageStatus::MESSAGE_AVAILABLE)
    {
        if (label == test2Msg_->getMessageLabel())
        {
            std::cout << getComponentLabel() << " receiving " << test2Msg_->getMessageLabel() << std::endl;
            receive(test2Msg_.get());

            std::cout << getComponentLabel() << " received " << test2Msg_->getMessageLabel() << " with data = " << test2Msg_->msg2data << std::endl;
        }

        status = peek(label);
    }

    test1Msg_->msg1data += 0.1;

    std::cout << getComponentLabel() << " sent " << test1Msg_->getMessageLabel() << " with data = " << test1Msg_->msg1data << std::endl;

    if (counter_ % 5 == 0)
    {
        send(test1Msg_.get());
    }

    test3Msg_->msg3data += 0.1;

    std::cout << getComponentLabel() << " sent " << test3Msg_->getMessageLabel() << " with data = " << test3Msg_->msg3data << std::endl;

    send(test3Msg_.get());

    counter_++;
}

void EomComponent::finalize(void)
{
    std::cout << getComponentLabel() << ": finalize()" << std::endl;
}