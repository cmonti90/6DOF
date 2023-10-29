#ifndef AUTOPILOT_COMPONENT_H
#define AUTOPILOT_COMPONENT_H


#include "Component.h"

#include <memory>

namespace TimePt
{
    class RtcClock;
}

namespace AutopilotTypes
{
    struct InData;
    struct OutData;
}

class AutopilotAlgorithm;

class AutopilotComponent : public PubSub::Component
{
  public:
    AutopilotComponent( std::shared_ptr<PubSub::QueueMngr>& queueMngr, const std::shared_ptr<TimePt::RtcClock>& sysClock, const PubSub::Component_Label name = "AutopilotComponent" );
    virtual ~AutopilotComponent();

    void initialize( void ) override;
    void update( void ) override;
    void finalize( void ) override;

  private:
    std::unique_ptr<AutopilotAlgorithm> pAlg;

    std::unique_ptr<AutopilotTypes::InData> inData_;
    std::unique_ptr<AutopilotTypes::OutData> outData_;

    std::shared_ptr<TimePt::RtcClock> sysClock_;

};

#endif /* AUTOPILOT_COMPONENT_H */