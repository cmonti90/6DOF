#ifndef EOMCOMPONENT_H
#define EOMCOMPONENT_H

#include "SimComponent.h"

namespace EomTypes
{
    struct InData;
    struct OutData;
}

class eom;

class EomComponent : public PubSub::SimComponent
{
public:
    EomComponent( std::shared_ptr<PubSub::QueueMngr> queueMngr, const PubSub::COMPONENT_LABEL name = "EomComponent" );
    virtual ~EomComponent();

    void initialize( void ) override;
    void update( void ) override;
    void finalize( void ) override;

private:
    std::unique_ptr<eom> pAlg;

    EomTypes::InData* inData_;
    EomTypes::OutData* outData_;

    unsigned int counter_;
};

#endif /* EOMCOMPONENT_H */