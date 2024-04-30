#ifndef LOWRATEAUTOPILOTCOMPONENT_H
#define LOWRATEAUTOPILOTCOMPONENT_H

#include "Component.h"

#include "PayloadEndpoint.h"

#include <memory>

namespace TimePt
{
    class RtcClock;
}

namespace LowRateAutopilotTypes
{
    struct InData;
    struct OutData;
}

class LowRateAutopilotAlgorithm;

class LowRateAutopilotComponent : public PubSub::Component
{
  public:

    LowRateAutopilotComponent( std::shared_ptr<PubSub::QueueMngr>& queueMngr,
                               const std::shared_ptr<TimePt::RtcClock>& sysClock,
                               const PubSub::Component_Label name = "LowRateAutopilotComponent" );

    virtual ~LowRateAutopilotComponent();

    void initialize( void ) override;
    void update( void ) override;
    void finalize( void ) override;

  protected:

    bool associateEvent() const override;

    static constexpr unsigned int active_endpoint_depth = 10u;
    static constexpr unsigned int passive_endpoint_depth = 10u;

  private:

    PubSub::PayloadEndpoint endpoint_;

    std::unique_ptr< LowRateAutopilotAlgorithm > pAlg_;

    std::unique_ptr< LowRateAutopilotTypes::InData  > inData_;
    std::unique_ptr< LowRateAutopilotTypes::OutData > outData_;

    std::shared_ptr<TimePt::RtcClock> sysClock_;
}; // class LowRateAutopilotComponent


#endif // LOWRATEAUTOPILOTCOMPONENT_H