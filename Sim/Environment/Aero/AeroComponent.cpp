
#include "AeroComponent.h"
#include "AeroTypes.h"

#include "Aero.h"

AeroComponent::AeroComponent(std::shared_ptr<PubSub::QueueMngr> queueMngr, const PubSub::COMPONENT_LABEL name)
    : PubSub::SimComponent(queueMngr, 1000, name), pAlg(new Aero()), inData_(new AeroTypes::InData()), outData_(new AeroTypes::OutData()), counter_(0u)
{
}

AeroComponent::~AeroComponent()
{
}

void AeroComponent::initialize(void)
{

    // subscribe( test2Msg_.get(), PubSub::Message_Type::ACTIVE );

    pAlg->initialize();
    counter_ = 0u;
}

void AeroComponent::update()
{

    PubSub::Message_Label label;
    PubSub::MessageStatus status = peek(label);

    while (status == PubSub::MessageStatus::MESSAGE_AVAILABLE)
    {
        switch (label)
        {
            // case test2Msg::MESSAGE_LABEL:
            //     receive( test2Msg_.get() );

        default:
            removeTopMessage();
            break;

            status = peek(label);
        }
    }

    // pAlg->exec();

    send<AeroMsg>(*outData_);

    counter_++;
}

void AeroComponent::finalize(void)
{
    pAlg->finalize();
}