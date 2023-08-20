#ifndef AEROCOMPONENT_H
#define AEROCOMPONENT_H

#include "SimComponent.h"

namespace AeroTypes
{
    struct InData;
    struct OutData;
}

class Aero;

class AeroComponent : public PubSub::SimComponent
{
public:
    AeroComponent( std::shared_ptr<PubSub::QueueMngr> queueMngr, const PubSub::COMPONENT_LABEL name = "AeroComponent" );
    virtual ~AeroComponent();

    void initialize( void ) override;
    void update( void ) override;
    void finalize( void ) override;

private:
    std::unique_ptr<Aero> pAlg;
    unsigned int counter_;

    AeroTypes::InData* inData_;
    AeroTypes::OutData* outData_;

};

#endif /* AEROCOMPONENT_H */