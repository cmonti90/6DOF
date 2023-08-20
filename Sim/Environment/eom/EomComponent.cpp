
#include "EomComponent.h"
#include "EomTypes.h"

#include "eom.h"

EomComponent::EomComponent(std::shared_ptr<PubSub::QueueMngr> queueMngr, const PubSub::COMPONENT_LABEL name)
    : PubSub::SimComponent(queueMngr, 1000, name),
      pAlg(new eom()),
      inData_(new EomTypes::InData()),
      outData_(new EomTypes::OutData()),
      counter_(0u)
{
}

EomComponent::~EomComponent()
{
}

void EomComponent::initialize(void)
{

    subscribe<AeroMsg>(*inData_);
    subscribe<EngineMsg>(*inData_);
    subscribe<GravityMsg>(*inData_);
    subscribe<MassPropMsg>(*inData_);

    pAlg->initialize();
    counter_ = 0u;
}

void EomComponent::update(void)
{

    PubSub::Message_Label label;
    PubSub::MessageStatus status = peek(label);

    while (status == PubSub::MessageStatus::MESSAGE_AVAILABLE)
    {
        switch (label)
        {
        case AeroMsg::MESSAGE_LABEL:
            receive<AeroMsg>(*inData_);

            pAlg->addForces(myMath::Vector3d(inData_->AeroData::force));
            pAlg->addMoments(myMath::Vector3d(inData_->AeroData::moment));

            break;

        case EngineMsg::MESSAGE_LABEL:
            receive<EngineMsg>(*inData_);

            pAlg->addForces(myMath::Vector3d(inData_->EngineData::force));
            pAlg->addMoments(myMath::Vector3d(inData_->EngineData::moment));

            break;

        case GravityMsg::MESSAGE_LABEL:
            receive<GravityMsg>(*inData_);

            pAlg->addForces(myMath::Vector3d(inData_->GravityData::force));

            break;

        case MassPropMsg::MESSAGE_LABEL:
            receive<MassPropMsg>(*inData_);

            break;

        default:
            removeTopMessage();
            break;
        }

        status = peek(label);
    }

    // pAlg->exec();

    send<EomMsg>(*outData_);

    counter_++;
}

void EomComponent::finalize(void)
{
    pAlg->finalize();
}