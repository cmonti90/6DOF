#ifndef CONTROL_SURFACES_H
#define CONTROL_SURFACES_H

#include "HwIntf.h"
#include "PayloadEndpoint.h"

#include <memory>

class Actuator;

namespace CtrlSurfTypes
{
    struct InData;
}

class ControlSurfaces : public SimLib::HwIntf
{
  public:
    ControlSurfaces( const double runRate, const std::string name = "ControlSurfaces" );
    ~ControlSurfaces();

  protected:

    PubSub::PayloadEndpoint endpoint_;

    std::unique_ptr< CtrlSurfTypes::InData > swInData_;

    Actuator* aileronL;
    Actuator* aileronR;
    Actuator* elevator;
    Actuator* rudder;

  private:

    virtual void initialize() override;
    virtual void update() override;
    virtual void finalize() override;

    void receiveQueueMngr( std::shared_ptr< PubSub::QueueMngr >& queueMngr );

    virtual void requestReferences( SimLib::ReferenceRequest& refReq ) override;

    ControlSurfaces( const ControlSurfaces& ) = delete;
    ControlSurfaces& operator=( const ControlSurfaces& ) = delete;
};

#endif /* CONTROL_SURFACES_H */