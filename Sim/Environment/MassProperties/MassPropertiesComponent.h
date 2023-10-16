#ifndef MASSPROPERTIESCOMPONENT_H
#define MASSPROPERTIESCOMPONENT_H

#include "SimComponent.h"

#include <memory>

namespace MassPropTypes
{
    struct InData;
    struct OutData;
}

class MassProperties;

class MassPropertiesComponent : public PubSub::SimComponent
{
public:
    MassPropertiesComponent(std::shared_ptr<PubSub::QueueMngr>& queueMngr, const PubSub::Component_Label name = "MassPropertiesComponent");
    virtual ~MassPropertiesComponent();

    void initialize(void) override;
    void update(void) override;
    void finalize(void) override;

private:
    std::unique_ptr<MassProperties> pAlg;

    std::unique_ptr<MassPropTypes::InData> inData_;
    std::unique_ptr<MassPropTypes::OutData> outData_;

    unsigned int counter_;
};

#endif /* MASSPROPERTIESCOMPONENT_H */