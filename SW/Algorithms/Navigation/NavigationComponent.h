#ifndef A6ADAB6A_3052_4300_85E1_E2ADB7292594
#define A6ADAB6A_3052_4300_85E1_E2ADB7292594

#include "Component.h"
#include "test1Msg.h"
#include "test2Msg.h"
#include "test3Msg.h"

#include <memory>

class NavigationComponent : public PubSub::Component
{
public:
    NavigationComponent(std::shared_ptr<PubSub::QueueMngr> queueMngr, const PubSub::COMPONENT_LABEL name = "NavigationComponent");
    virtual ~NavigationComponent();

    void initialize(void) override;
    void update(void) override;
    void finalize(void) override;

    std::unique_ptr<test1Msg> test1Msg_;
    std::unique_ptr<test2Msg> test2Msg_;
    std::unique_ptr<test3Msg> test3Msg_;

};

#endif /* A6ADAB6A_3052_4300_85E1_E2ADB7292594 */
