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
    void GetFinDeflections( float ( &finPosOut )[4] ) const;

  protected:

    virtual void initialize() override;
    virtual void update() override;
    virtual void finalize() override;
    virtual void receiveQueueMngr( std::shared_ptr< PubSub::QueueMngr >& queueMngr ) override;

    void CheckForMessages();

    PubSub::PayloadEndpoint endpoint_;

    std::unique_ptr< CtrlSurfTypes::InData > swInData_;

    std::unique_ptr< Actuator > fin1_;
    std::unique_ptr< Actuator > fin2_;
    std::unique_ptr< Actuator > fin3_;
    std::unique_ptr< Actuator > fin4_;

  private:

    ControlSurfaces( const ControlSurfaces& ) = delete;
    ControlSurfaces& operator=( const ControlSurfaces& ) = delete;
};

#endif /* CONTROL_SURFACES_H */