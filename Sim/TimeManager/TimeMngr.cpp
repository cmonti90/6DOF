#include "TimeMngr.h"

TimeMngr::TimeMngr() :  dt(),
                        simTime(),
                        validEncTime()
{}

void TimeMngr::initialize(void)
{
    dt = 0.0001;
    simTime = 0.0;
}

void TimeMngr::update(void)
{
    simTime += dt;
}

double TimeMngr::getTimeNow(void)
{
    return simTime;
}