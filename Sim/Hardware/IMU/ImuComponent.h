#ifndef IMUCOMPONENT_H
#define IMUCOMPONENT_H

#include "SimComponent.h"

#include <memory>

namespace ImuTypes
{
    struct InData;
    struct OutData;
}

class Imu;

class ImuComponent : public PubSub::SimComponent
{
public:
    ImuComponent(std::shared_ptr<PubSub::QueueMngr> queueMngr, const PubSub::COMPONENT_LABEL name = "ImuComponent");
    virtual ~ImuComponent();

    void initialize(void) override;
    void update(void) override;
    void finalize(void) override;

private:
    std::unique_ptr<Imu> pAlg;

    std::unique_ptr<ImuTypes::InData> inData_;
    std::unique_ptr<ImuTypes::OutData> outData_;

    unsigned int counter_;
};

#endif /* IMUCOMPONENT_H */