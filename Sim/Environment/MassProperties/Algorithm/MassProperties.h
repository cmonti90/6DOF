#ifndef AERO_H
#define AERO_H

#include "MassPropertiesTypes.h"

#include "mathlib.h"

class MassProperties
{
protected:

public:
    MassProperties();
    ~MassProperties();

    void initialize(void);
    void exec(const MassPropTypes::InData &inData, MassPropTypes::OutData &outData);
    void finalize(void);
};

#endif /* AERO_H */