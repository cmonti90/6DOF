
#ifndef GUIDANCECOMPONENT_H
#define GUIDANCECOMPONENT_H

#include "Component.h"
#include "test1Msg.h"
#include "test2Msg.h"
#include "test3Msg.h"

#include <memory>

class GuidanceComponent : public PubSub::Component
{
public:
    GuidanceComponent(std::shared_ptr<PubSub::QueueMngr> queueMngr, const PubSub::COMPONENT_LABEL name = "GuidanceComponent");
    virtual ~GuidanceComponent();

    void initialize(void) override;
    void update(void) override;
    void finalize(void) override;

    std::unique_ptr<test1Msg> test1Msg_;
    std::unique_ptr<test2Msg> test2Msg_;
    std::unique_ptr<test3Msg> test3Msg_;

};

#endif /* GUIDANCECOMPONENT_H */
