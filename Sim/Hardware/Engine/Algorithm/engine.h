#ifndef ENGINE_H
#define ENGINE_H

#include "TimeMngr.h"
#include "mathlib.h"

class engine
{
public:
    engine();
    ~engine();

    void initialize(void);
    void exec(void);
    void finalize(void);

protected:
    double ctrlInput;

    myMath::Vector3d netForceBody;
    myMath::Vector3d netMomentBody;
};

#endif /* ENGINE_H */