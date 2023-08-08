#ifndef AUTOPILOT_COMPONENT_H
#define AUTOPILOT_COMPONENT_H


#include "Component.h"
#include "test1Msg.h"
#include "test2Msg.h"
#include "test3Msg.h"

#include <memory>

class AutopilotComponent : public PubSub::Component
{
public:
    AutopilotComponent(std::shared_ptr<PubSub::QueueMngr> queueMngr, const PubSub::COMPONENT_LABEL name = "AutopilotComponent");
    virtual ~AutopilotComponent();

    void initialize(void) override;
    void update(void) override;
    void finalize(void) override;

    std::unique_ptr<test1Msg> test1Msg_;
    std::unique_ptr<test2Msg> test2Msg_;
    std::unique_ptr<test3Msg> test3Msg_;

};

#endif /* AUTOPILOT_COMPONENT_H */