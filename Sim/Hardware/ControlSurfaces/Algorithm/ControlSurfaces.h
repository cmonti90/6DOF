#ifndef CONTROL_SURFACES_H
#define CONTROL_SURFACES_H

#include "ControlSurfacesTypes.h"

class CtrlSurfs
{
public:
    CtrlSurfs();
    ~CtrlSurfs();

    void initialize(void);
    void exec(const CtrlSurfTypes::InData& inData, CtrlSurfTypes::OutData& outData);
    void finalize(void);

protected:
    double aileronDefl[2];
    double elevatorDefl;
    double rudderDefl;

    void BuildOutput(CtrlSurfTypes::OutData& outData);

};

#endif /* CONTROL_SURFACES_H */