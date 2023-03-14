#ifndef RUNNER_H
#define RUNNER_H

#include <iostream>
#include "TimeMngr.h"
#include "eom.h"
#include "mathlib.h"

double tf{0.0};
unsigned int counter{0};

void getSimReferences(void);
void initializeSim(void);
void runSim(void);
void finalizeSim(void);

class runner
{
public:
    TimeMngr *pTimeMngr_ = new TimeMngr();
    eom *pEom_ = new eom();
};

runner wrapper;

#endif