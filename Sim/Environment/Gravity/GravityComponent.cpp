
#include "GravityTypes.h"
#include "GravityComponent.h"

#include "Gravity.h"

GravityComponent::GravityComponent(std::shared_ptr<PubSub::QueueMngr> queueMngr, const PubSub::COMPONENT_LABEL name)
    : PubSub::SimComponent(queueMngr, 1000, name),
      pAlg(new Gravity()),
      inData_(new GravityTypes::InData()),
      outData_(new GravityTypes::OutData()),
      counter_(0u)
{
}

GravityComponent::~GravityComponent()
{
}

void GravityComponent::initialize(void)
{

    subscribe<EomMsg>(*inData_);

    pAlg->initialize();
    counter_ = 0u;
}

void GravityComponent::update()
{

    PubSub::Message_Label label;
    PubSub::MessageStatus status = peek(label);

    while (status == PubSub::MessageStatus::MESSAGE_AVAILABLE)
    {
        switch (label)
        {
        case EomMsg::MESSAGE_LABEL:
            receive<EomMsg>(*inData_);
            break;

        default:
            removeTopMessage();
            break;
        }

        status = peek(label);
    }

    // pAlg->exec();

    send<GravityMsg>(*outData_);

    counter_++;
}

void GravityComponent::finalize(void)
{
    pAlg->finalize();
}