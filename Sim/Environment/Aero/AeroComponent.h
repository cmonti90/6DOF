#ifndef AEROCOMPONENT_H
#define AEROCOMPONENT_H

#include "SimComponent.h"

#include <memory>

namespace AeroTypes
{
    struct InData;
    struct OutData;
}

class Aero;

class AeroComponent : public PubSub::SimComponent
{
public:
    AeroComponent( std::shared_ptr<PubSub::QueueMngr> queueMngr, const PubSub::Component_Label name = "AeroComponent" );
    virtual ~AeroComponent();

    void initialize( void ) override;
    void update( void ) override;
    void finalize( void ) override;

private:
    std::unique_ptr<Aero> pAlg;
    unsigned int counter_;

    std::unique_ptr<AeroTypes::InData> inData_;
    std::unique_ptr<AeroTypes::OutData> outData_;

};

#endif /* AEROCOMPONENT_H */