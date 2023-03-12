#ifndef RUNNER_H
#define RUNNER_H

#include <iostream>
#include "TimeMngr.h"
#include "eom.h"
#include "Encoder.h"
#include "Motor.h"
#include "Navigation.h"
#include "Controller.h"
#include "imu.h"

double tf{0.0};
unsigned int counter{0};

void getSimReferences(void);
void getSwReferences(void);
void initializeSim(void);
void initializeSW(void);
void runSim(void);
void runSW(void);
void getOutputs(void);
void finalizeSim(void);
void finalizeSW(void);

class runner
{
public:
    TimeMngr *pTimeMngr_ = new TimeMngr();
    eom *pEom_ = new eom();
    Motor *pMtr_ = new Motor();
    imu *pImu_ = new imu();
    Encoder *pEnc_ = new Encoder();

    Nav *pNav_ = new Nav();
    Controller *pCon_ = new Controller();
};

runner wrapper;

#endif