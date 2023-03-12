#ifndef IMU_H
#define IMU_H

#include <iostream>
#include <array>
#include "eom.h"
#include "TimeMngr.h"

class imu
{
protected:
    TimeMngr *pTimeMngr;
    eom *pEom_;

    double xbdotdot{0.0};

    double mb{0.0};

public:
    imu();
    ~imu();
    imu(const imu &obj);
    imu &operator=(const imu &);
    void getImuReferences(TimeMngr *refTimeMngr, eom *refEom);
    void initialize(void);
    void exec(void);

    void setEomOutputsImu()
    {
        xbdotdot = pEom_->getEomXbdotdot();
    }

    double getImuXbdotdot(void)
    {
        return xbdotdot;
    };
};

#endif