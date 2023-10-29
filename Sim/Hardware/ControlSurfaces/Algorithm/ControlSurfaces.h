#ifndef CONTROL_SURFACES_H
#define CONTROL_SURFACES_H

#include "ControlSurfacesTypes.h"

#include <memory>

class Actuator;

class CtrlSurfs
{
public:
    CtrlSurfs();
    ~CtrlSurfs();

    void initialize(void);
    void exec(const CtrlSurfTypes::InData& inData, CtrlSurfTypes::OutData& outData);
    void finalize(void);

protected:
    void BuildOutput(CtrlSurfTypes::OutData& outData);

    Actuator* aileronL;
    Actuator* aileronR;
    Actuator* elevator;
    Actuator* rudder;

};

#endif /* CONTROL_SURFACES_H */