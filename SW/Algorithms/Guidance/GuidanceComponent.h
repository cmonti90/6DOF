
#ifndef GUIDANCECOMPONENT_H
#define GUIDANCECOMPONENT_H

#include "Component.h"

#include "PayloadEndpoint.h"

#include <memory>

namespace TimePt
{
    class RtcClock;
}

namespace GuidanceTypes
{
    struct InData;
    struct OutData;
}

class GuidanceAlgorithm;

class GuidanceComponent : public PubSub::Component
{
  public:
    GuidanceComponent( std::shared_ptr<PubSub::QueueMngr>& queueMngr, const std::shared_ptr<TimePt::RtcClock>& sysClock, const PubSub::Component_Label name = "GuidanceComponent" );
    virtual ~GuidanceComponent();

    void initialize( void ) override;
    void update( void ) override;
    void finalize( void ) override;

  protected:
    bool associateEvent() const override;

    static constexpr unsigned int active_endpoint_depth = 10u;
    static constexpr unsigned int passive_endpoint_depth = 10u;

  private:
    PubSub::PayloadEndpoint endpoint_;

    std::unique_ptr<GuidanceAlgorithm> pAlg;

    std::unique_ptr<GuidanceTypes::InData> inData_;
    std::unique_ptr<GuidanceTypes::OutData> outData_;

    std::shared_ptr<TimePt::RtcClock> sysClock_;
};

#endif /* GUIDANCECOMPONENT_H */
