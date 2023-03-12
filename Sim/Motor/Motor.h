#ifndef MOTOR_H
#define MOTOR_H

#include "TimeMngr.h"
#include <iostream>
#include <array>

class Motor
{
protected:
    TimeMngr *pTimeMngr;

    double omega{0.0};
    double omegadot{0.0};
    double I{0.0};
    double i{0.0};
    double idot{0.0};
    double L{0.0};

    double cmd{0.0};

    int check{0};

public:
    Motor();
    Motor(const Motor &obj);
    ~Motor();

    Motor &operator=(const Motor &x)
    {
        *this = x;
        return *this;
    }

    void getMotorReferences(TimeMngr *ref);
    void initialize(void);
    void exec(void);
    
    void setControllerOutput(const double inCmd)
    {
        cmd = inCmd;
    }

    double getMotorOutput(void)
    {
        return omegadot;
    }
};

#endif