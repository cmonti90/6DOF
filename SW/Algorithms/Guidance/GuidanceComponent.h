
#ifndef GUIDANCECOMPONENT_H
#define GUIDANCECOMPONENT_H

#include "Component.h"
#include "test1Msg.h"
#include "test2Msg.h"

#include <memory>

namespace GuidanceTypes
{
    struct InData;
    struct OutData;
}

class GuidanceAlgorithm;

class GuidanceComponent : public PubSub::Component
{
public:
    GuidanceComponent(std::shared_ptr<PubSub::QueueMngr> queueMngr, const PubSub::COMPONENT_LABEL name = "GuidanceComponent");
    virtual ~GuidanceComponent();

    void initialize(void) override;
    void update(void) override;
    void finalize(void) override;

private:
    std::unique_ptr<GuidanceAlgorithm> pAlg;

    std::unique_ptr<GuidanceTypes::InData> inData_;
    std::unique_ptr<GuidanceTypes::OutData> outData_;

};

#endif /* GUIDANCECOMPONENT_H */
