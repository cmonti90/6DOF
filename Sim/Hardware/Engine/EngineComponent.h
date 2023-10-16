#ifndef ENGINECOMPONENT_H
#define ENGINECOMPONENT_H

#include "SimComponent.h"

#include <memory>

namespace EngineTypes
{
    struct InData;
    struct OutData;
}

class engine;

class EngineComponent : public PubSub::SimComponent
{
public:
    EngineComponent(std::shared_ptr<PubSub::QueueMngr>& queueMngr, const PubSub::Component_Label name = "EngineComponent");
    virtual ~EngineComponent();

    void initialize(void) override;
    void update(void) override;
    void finalize(void) override;

private:
    std::unique_ptr<engine> pAlg;

    std::unique_ptr<EngineTypes::InData> inData_;
    std::unique_ptr<EngineTypes::OutData> outData_;

    unsigned int counter_;
};

#endif /* ENGINECOMPONENT_H */