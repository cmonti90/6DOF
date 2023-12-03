#ifndef IMUCOMPONENT_H
#define IMUCOMPONENT_H

#include "SimComponent.h"

#include "PayloadEndpoint.h"

#include <memory>

namespace TimePt
{
    class RtcClock;
}

namespace ImuTypes
{
    struct InData;
    struct OutData;
}

class Imu;

class ImuComponent : public PubSub::SimComponent
{
public:
    ImuComponent(std::shared_ptr<PubSub::QueueMngr>& queueMngr, const std::shared_ptr<TimePt::RtcClock>& sysClock, const PubSub::Component_Label name = "ImuComponent");
    virtual ~ImuComponent();

    void initialize(void) override;
    void update(void) override;
    void finalize(void) override;

private:
    PubSub::PayloadEndpoint endpoint_;
    
    std::unique_ptr<Imu> pAlg;

    std::unique_ptr<ImuTypes::InData> inData_;
    std::unique_ptr<ImuTypes::OutData> outData_;

    std::shared_ptr<TimePt::RtcClock> sysClock_;

    unsigned int counter_;
};

#endif /* IMUCOMPONENT_H */