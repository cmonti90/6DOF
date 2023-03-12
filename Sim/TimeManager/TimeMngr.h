#ifndef TIMEMNGR_H
#define TIMEMNGR_H

#include <iostream>

class TimeMngr
{
private:
    double dt;
    double simTime;
    double validEncTime;

public:
    TimeMngr(void);
    void initialize(void);
    void update(void);
    double getTimeNow(void);
};

#endif