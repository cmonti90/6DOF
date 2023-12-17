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

    // Getters
    double getAileronLDeflection() const;
    double getAileronRDeflection() const;
    double getElevatorDeflection() const;
    double getRudderDeflection() const;

  protected:

    virtual void initialize() override;
    virtual void update() override;
    virtual void finalize() override;
    virtual void receiveQueueMngr( std::shared_ptr< PubSub::QueueMngr >& queueMngr ) override;

    void CheckForMessages();

    PubSub::PayloadEndpoint endpoint_;

    std::unique_ptr< CtrlSurfTypes::InData > swInData_;

    Actuator* aileronL_;
    Actuator* aileronR_;
    Actuator* elevator_;
    Actuator* rudder_;

  private:

    ControlSurfaces( const ControlSurfaces& ) = delete;
    ControlSurfaces& operator=( const ControlSurfaces& ) = delete;
};

#endif /* CONTROL_SURFACES_H */