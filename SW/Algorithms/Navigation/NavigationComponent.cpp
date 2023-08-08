
#include "NavigationComponent.h"

#include <iostream>

NavigationComponent::NavigationComponent(std::shared_ptr<PubSub::QueueMngr> queueMngr, const PubSub::COMPONENT_LABEL name)
: PubSub::Component(queueMngr, name), test1Msg_(new test1Msg()), test2Msg_(new test2Msg()), test3Msg_(new test3Msg())
{
}

NavigationComponent::~NavigationComponent()
{
}

void NavigationComponent::initialize(void)
{
    std::cout << getComponentLabel() << ": initialize()" << std::endl;

    std::cout << getComponentLabel() << ": subscribing to " << test1Msg_->getMessageLabel() << std::endl;

    subscribe(test1Msg_.get(), PubSub::Message_Type::ACTIVE);

    std::cout << getComponentLabel() << ": subscribed to " << test1Msg_->getMessageLabel() << std::endl;

    subscribe(test3Msg_.get(), PubSub::Message_Type::PASSIVE);
}

void NavigationComponent::update(void)
{
    PubSub::Message_Label label;
    PubSub::MessageStatus status = peek(label);

    std::cout << getComponentLabel() << "::update()" << std::endl;

    std::cout << getComponentLabel() << " peeked: ";
    std::cout << "status = " << status << ", label = " << label << std::endl;

    while (status == PubSub::MessageStatus::MESSAGE_AVAILABLE)
    {
        if (label == test1Msg_->getMessageLabel())
        {
            std::cout << getComponentLabel() << " receiving " << test1Msg_->getMessageLabel() << std::endl;
            receive(test1Msg_.get());

            std::cout << getComponentLabel() << " received " << test1Msg_->getMessageLabel() << " with data = " << test1Msg_->msg1data << std::endl;

            test2Msg_->msg2data += 0.1;

            send(test2Msg_.get());

            std::cout << getComponentLabel() << " sent " << test2Msg_->getMessageLabel() << " with data = " << test2Msg_->msg2data << std::endl;
        }
        else if (label == test3Msg_->getMessageLabel())
        {
            std::cout << getComponentLabel() << " receiving " << test3Msg_->getMessageLabel() << std::endl;
            receive(test3Msg_.get());

            std::cout << getComponentLabel() << " received " << test3Msg_->getMessageLabel() << " with data = " << test3Msg_->msg3data << std::endl;
        }

        status = peek(label);
    }
}

void NavigationComponent::finalize(void)
{
    std::cout << getComponentLabel() << ": finalize()" << std::endl;
}