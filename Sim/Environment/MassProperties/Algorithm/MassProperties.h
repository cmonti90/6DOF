#ifndef AERO_H
#define AERO_H

#include <iostream>
#include <array>
#include "TimeMngr.h"
#include "mathlib.h"

class MassProperties
{
protected:

public:
    MassProperties();
    ~MassProperties();

    void initialize(void);
    void exec(void);
    void finalize(void);
};

#endif /* AERO_H */