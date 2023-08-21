
#include "GuidanceComponent.h"
#include "GuidanceTypes.h"
#include "GuidanceAlgorithm.h"
#include "TryCatch.h"

#include <iostream>

GuidanceComponent::GuidanceComponent(std::shared_ptr<PubSub::QueueMngr> queueMngr, const PubSub::COMPONENT_LABEL name)
    : PubSub::Component(queueMngr, name),
      pAlg(new GuidanceAlgorithm()),
      inData_(new GuidanceTypes::InData()),
      outData_(new GuidanceTypes::OutData())
{
}

GuidanceComponent::~GuidanceComponent()
{
}

void GuidanceComponent::initialize(void)
{

    subscribe<NavMsg>(*inData_, PubSub::Message_Type::ACTIVE);

    pAlg->initialize();
}

void GuidanceComponent::update(void)
{
    BEGIN_CHECKED_EXCEPTION()
    {
        PubSub::Message_Label label;
        PubSub::MessageStatus status = peek(label);

        while (status == PubSub::MessageStatus::MESSAGE_AVAILABLE)
        {
            switch (label)
            {
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
    END_CHECKED_EXCEPTION()
}

void GuidanceComponent::finalize(void)
{
    pAlg->finalize();
}