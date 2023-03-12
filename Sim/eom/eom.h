#ifndef EOM_H
#define EOM_H

#include <iostream>
#include <array>
#include "Motor.h"
#include "TimeMngr.h"

class eom
{
protected:
    TimeMngr *pTimeMngr;
    Motor *pMtr_;

    double dt{0.0};
    double t{0.0};
    int counter{0};

    double xbdotdot_{0.0};
    double xbdot_{0.0};
    double xb_{0.0};

    double xrdotdot{0.0};
    double xrdot{0.0};
    double xr{0.0};

    double thetadotdot_{0.0};
    double thetadot_{0.0};
    double theta_{0.0};

    double mb{0.0};
    double mr{0.0};
    double Len{0.0};
    double I{0.0};
    double g{0.0};
    double PI{0.0};

    double Frg{0.0};
    double Ff{0.0};
    double Ff_mag{0.0};
    double Mf{0.0};
    double Mf_mag{0.0};

    double motorAccel{0.0};

    void getMotorOutput(void);
    void rungeKutta4thOrder(void);
    double thetaDotDotOde(double xbdotdot, double theta);
    double xbDotDotOde(double xbdotdot, double theta);

public:
    eom();
    ~eom();
    eom(const eom &obj);
    eom &operator=(const eom &obj);
    void getEomReferences(TimeMngr * refTimeMngr, Motor *refMotor);
    void initialize(void);
    void exec(void);
    void setMotorDynamics(void);

    double getEomTheta(void)
    {
        return theta_;
    }

    double getEomXbdotdot(void)
    {
        return xbdotdot_;
    }
};

#endif