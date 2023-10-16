#ifndef EOMCOMPONENT_H
#define EOMCOMPONENT_H

#include "SimComponent.h"

#include <memory>

namespace TimePt
{
    class RtcClock;
}

namespace EomTypes
{
    struct InData;
    struct OutData;
}

class eom;

class EomComponent : public PubSub::SimComponent
{
public:
    EomComponent( std::shared_ptr<PubSub::QueueMngr>& queueMngr, std::shared_ptr<TimePt::RtcClock>& sysClock, const PubSub::Component_Label name = "EomComponent" );
    virtual ~EomComponent();

    void initialize( void ) override;
    void update( void ) override;
    void finalize( void ) override;

private:
    std::unique_ptr<eom> pAlg;

    std::unique_ptr<EomTypes::InData> inData_;
    std::unique_ptr<EomTypes::OutData> outData_;

    std::shared_ptr<TimePt::RtcClock> sysClock_;

    unsigned int counter_;

};

#endif /* EOMCOMPONENT_H */