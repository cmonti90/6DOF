#ifndef CONTROL_SURFACES_H
#define CONTROL_SURFACES_H

#include "TimeMngr.h"
#include "mathlib.h"

class CtrlSurfs
{
public:
    CtrlSurfs();
    ~CtrlSurfs();

    void initialize(void);
    void exec(void);
    void finalize(void);

protected:
    double ctrlInput;

    myMath::Vector3d netForceBody;
    myMath::Vector3d netMomentBody;
};

#endif /* CONTROL_SURFACES_H */