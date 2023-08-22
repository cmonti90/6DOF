#ifndef A6ADAB6A_3052_4300_85E1_E2ADB7292594
#define A6ADAB6A_3052_4300_85E1_E2ADB7292594

#include "Component.h"

#include <memory>
namespace NavTypes
{
    struct InData;
    struct OutData;
}

class NavigationAlgorithm;

namespace TimePt
{
    class RtcClock;
}

class NavigationComponent : public PubSub::Component
{
public:
    NavigationComponent(std::shared_ptr<PubSub::QueueMngr> queueMngr,
                        const std::shared_ptr<TimePt::RtcClock> rtcClock,
                        const PubSub::COMPONENT_LABEL name = "NavigationComponent");
    virtual ~NavigationComponent();

    void initialize(void) override;
    void update(void) override;
    void finalize(void) override;

private:
    std::unique_ptr<NavigationAlgorithm> pAlg;

    std::unique_ptr<NavTypes::InData> inData_;
    std::unique_ptr<NavTypes::OutData> outData_;
};

#endif /* A6ADAB6A_3052_4300_85E1_E2ADB7292594 */
