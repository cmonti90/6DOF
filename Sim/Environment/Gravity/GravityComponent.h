#ifndef GRAVITYCOMPONENT_H
#define GRAVITYCOMPONENT_H

#include "SimComponent.h"

#include <memory>

namespace GravityTypes
{
    struct InData;
    struct OutData;
}

class Gravity;

class GravityComponent : public PubSub::SimComponent
{
public:
    GravityComponent( std::shared_ptr<PubSub::QueueMngr> queueMngr, const PubSub::Component_Label name = "GravityComponent" );
    virtual ~GravityComponent();

    void initialize( void ) override;
    void update( void ) override;
    void finalize( void ) override;

private:
    std::unique_ptr<Gravity> pAlg;
    unsigned int counter_;

    std::unique_ptr<GravityTypes::InData> inData_;
    std::unique_ptr<GravityTypes::OutData> outData_;

};

#endif /* GRAVITYCOMPONENT_H */