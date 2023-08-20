#ifndef F5CC6C97_3A30_42E3_BD6F_E859839898B5
#define F5CC6C97_3A30_42E3_BD6F_E859839898B5

#include "Module.h"

#include <memory>

namespace TimePt
{
    class RtcClock;
}

// Simulation Component forward declarations
class MassPropertiesComponent;
class EngineComponent;
class AeroComponent;
class EomComponent;

// SW Component forward declarations
class NavigationComponent;
class GuidanceComponent;
class AutopilotComponent;

class ProcModule : public PubSub::Module
{
public:
    ProcModule();
    virtual ~ProcModule();

    void launch();

private:
    std::shared_ptr<TimePt::RtcClock> pRtcClock;

    PubSub::Thread navThread;
    PubSub::Thread guidanceThread;
    PubSub::Thread autopilotThread;

    std::unique_ptr<MassPropertiesComponent> pMassPropComponent;
    std::unique_ptr<EngineComponent> pEngineComponent;
    std::unique_ptr<EomComponent> pEomComponent;
    std::unique_ptr<AeroComponent> pAeroComponent;

    std::unique_ptr<NavigationComponent> pNavigationComponent;
    std::unique_ptr<GuidanceComponent> pGuidanceComponent;
    std::unique_ptr<AutopilotComponent> pAutopilotComponent;

};

#endif /* F5CC6C97_3A30_42E3_BD6F_E859839898B5 */
