#ifndef CONTROL_SURFACES_H
#define CONTROL_SURFACES_H

#include "ControlSurfacesTypes.h"

#include <memory>

class Actuation;

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

    Actuation* aileronL;
    Actuation* aileronR;
    Actuation* elevator;
    Actuation* rudder;

};

#endif /* CONTROL_SURFACES_H */