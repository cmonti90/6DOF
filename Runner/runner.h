#ifndef RUNNER_H
#define RUNNER_H

#include <iostream>
// #include "TimeMngr.h"
// #include "eom.h"
// #include "mathlib.h"

#include "ProcModule.h"
#include <pthread.h>
#include <thread>

double tf{0.0};
unsigned int counter{0};

void getSimReferences(void);
void initializeSim(void);
void runSim(void);
void finalizeSim(void);

class runner
{
public:
    // TimeMngr *pTimeMngr_ = new TimeMngr();
    // eom *pEom_ = new eom();

    ProcModule pProcModule_;
};

runner wrapper;

#endif