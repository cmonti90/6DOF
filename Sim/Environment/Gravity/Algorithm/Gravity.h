#ifndef GRAVITY_H
#define GRAVITY_H

#include "TimeMngr.h"
#include "mathlib.h"
#include "GravityTypes.h"

class Gravity
{
protected:

public:
    Gravity();
    ~Gravity();

    void initialize(void);
    void exec(const GravityTypes::InData& inData, GravityTypes::OutData& outData);
    void finalize(void);

protected:
    myMath::Vector3d gravForceNed;

    void BuildOutput(const GravityTypes::InData& inData, GravityTypes::OutData& outData);

private:
    Gravity& operator=(const Gravity& orig) = delete;
    Gravity(const Gravity& orig) = delete;
};

#endif /* GRAVITY_H */