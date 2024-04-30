#ifndef HIGHRATEAUTOPILOT_COMPONENT_H
#define HIGHRATEAUTOPILOT_COMPONENT_H


#include "Component.h"

#include "PayloadEndpoint.h"

#include <memory>

namespace TimePt
{
    class RtcClock;
}

namespace HighRateAutopilotTypes
{
    struct InData;
    struct OutData;
}

class HighRateAutopilotAlgorithm;

class HighRateAutopilotComponent : public PubSub::Component
{
  public:
    HighRateAutopilotComponent( std::shared_ptr<PubSub::QueueMngr>& queueMngr,
                        const std::shared_ptr<TimePt::RtcClock>& sysClock,
                        const PubSub::Component_Label name = "HighRateAutopilotComponent" );
    virtual ~HighRateAutopilotComponent();

    void initialize( void ) override;
    void update( void ) override;
    void finalize( void ) override;

  protected:
    bool associateEvent() const override;

    static constexpr unsigned int active_endpoint_depth = 10u;
    static constexpr unsigned int passive_endpoint_depth = 10u;

  private:
    PubSub::PayloadEndpoint endpoint_;

    std::unique_ptr< HighRateAutopilotAlgorithm > pAlg_;

    std::unique_ptr< HighRateAutopilotTypes::InData  > inData_;
    std::unique_ptr< HighRateAutopilotTypes::OutData > outData_;

    std::shared_ptr< TimePt::RtcClock > sysClock_;

};

#endif // HIGHRATEAUTOPILOT_COMPONENT_H