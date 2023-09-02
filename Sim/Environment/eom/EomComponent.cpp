
#include "EomComponent.h"
#include "EomTypes.h"

#include "eom.h"

EomComponent::EomComponent(std::shared_ptr<PubSub::QueueMngr> queueMngr, const PubSub::Component_Label name)
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
    inData_->initialize();
    outData_->initialize();

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

            pAlg->addForces(inData_->AeroData::forceBody);
            pAlg->addMoments(inData_->AeroData::momentBody);

            break;

        case EngineMsg::MESSAGE_LABEL:
            receive<EngineMsg>(*inData_);

            pAlg->addForces(inData_->EngineData::forceBody);
            pAlg->addMoments(inData_->EngineData::momentBody);

            break;

        case GravityMsg::MESSAGE_LABEL:
            receive<GravityMsg>(*inData_);

            pAlg->addForces(inData_->GravityData::forceBody);

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

    pAlg->exec(*inData_, *outData_);

    send<EomMsg>(*outData_);

    counter_++;

    testing();
}

void EomComponent::finalize(void)
{
    pAlg->finalize();
}

#include "mathlib.h"
#include <iostream>

void EomComponent::testing()
{
    myMath::AngleD ang;
    ang[0] = 30.0 * myMath::Constants::DEG_TO_RAD;
    ang[1] = 15.0 * myMath::Constants::DEG_TO_RAD;
    ang[2] = 40.0 * myMath::Constants::DEG_TO_RAD;

    myMath::DCMd dcm = ang.ToDCM(myMath::EulerOrder::ZXZ);

    std::cout << "DCM: " << std::endl;
    std::cout << dcm[0][0] << "  " << dcm[0][1] << "  " << dcm[0][2] << std::endl;
    std::cout << dcm[1][0] << "  " << dcm[1][1] << "  " << dcm[1][2] << std::endl;
    std::cout << dcm[2][0] << "  " << dcm[2][1] << "  " << dcm[2][2] << std::endl;
    std::cout << std::endl;
    std::cout << std::endl;

}