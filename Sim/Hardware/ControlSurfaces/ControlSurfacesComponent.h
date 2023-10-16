#ifndef CONTROLSURFACESCOMPONENT_H
#define CONTROLSURFACESCOMPONENT_H

#include "SimComponent.h"

#include <memory>

namespace TimePt
{
    class RtcClock;
}

namespace CtrlSurfTypes
{
    struct InData;
    struct OutData;
}

class CtrlSurfs;

class ControlSurfacesComponent : public PubSub::SimComponent
{
public:
    ControlSurfacesComponent(std::shared_ptr<PubSub::QueueMngr>& queueMngr, std::shared_ptr<TimePt::RtcClock>& sysClock, const PubSub::Component_Label name = "ControlSurfacesComponent");
    virtual ~ControlSurfacesComponent();

    void initialize(void) override;
    void update(void) override;
    void finalize(void) override;

private:
    std::unique_ptr<CtrlSurfs> pAlg;

    std::unique_ptr<CtrlSurfTypes::InData> inData_;
    std::unique_ptr<CtrlSurfTypes::OutData> outData_;

    std::shared_ptr<TimePt::RtcClock> sysClock_;

    unsigned int counter_;
};

#endif /* CONTROLSURFACESCOMPONENT_H */