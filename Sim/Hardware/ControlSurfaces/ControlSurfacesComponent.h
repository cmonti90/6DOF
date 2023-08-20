#ifndef CONTROLSURFACESCOMPONENT_H
#define CONTROLSURFACESCOMPONENT_H

#include "SimComponent.h"

#include <memory>

namespace CtrlSurfTypes
{
    struct InData;
    struct OutData;
}

class CtrlSurfs;

class ControlSurfacesComponent : public PubSub::SimComponent
{
public:
    ControlSurfacesComponent(std::shared_ptr<PubSub::QueueMngr> queueMngr, const PubSub::COMPONENT_LABEL name = "ControlSurfacesComponent");
    virtual ~ControlSurfacesComponent();

    void initialize(void) override;
    void update(void) override;
    void finalize(void) override;

private:
    std::unique_ptr<CtrlSurfs> pAlg;

    std::unique_ptr<CtrlSurfTypes::InData> inData_;
    std::unique_ptr<CtrlSurfTypes::OutData> outData_;

    unsigned int counter_;
};

#endif /* CONTROLSURFACESCOMPONENT_H */