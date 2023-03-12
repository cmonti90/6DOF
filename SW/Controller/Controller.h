#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <iostream>
#include <array>
#include "Navigation.h"
#include "TimeMngr.h"
#include "mathlib.h"

class Controller
{
protected:
    TimeMngr *pTimeMngr;
    Nav *pNav;

    double dt{0.0};

    myMath::Vector3d xbStates_{0.0};
    double xbdotdot_prev{0.0};
    double xbdot_prev{0.0};
    double xbdotdot{0.0};
    double xbdot{0.0};
    double xb{0.0};

    myMath::Vector3d xrStates_{0.0};
    myMath::Vector<double, 6> xrdotdot_prev{0.0};
    myMath::Vector<double, 6> xrdot_prev{0.0};
    double xrdotdot{0.0};
    double xrdot{0.0};
    double xr{0.0};

    myMath::Vector3d thetaStates_{0.0};
    myMath::Vector<double, 6> thetadotdot_prev{0.0};
    myMath::Vector<double, 6> thetadot_prev{0.0};
    double thetadotdot{0.0};
    double thetadot{0.0};
    double theta{0.0};

    double mb{0.0};
    double mr{0.0};
    double pivot_to_cm{0.0};
    double I{0.0};

    double Frg{0.0};
    double Ff{0.0};

    double cmd{0.0};

    void getNavStates(void);
    void controlLaw(void);
    void outputToMotor(void);

public:
    Controller(){};
    ~Controller();
    Controller(const Controller &obj);
    Controller &operator=(const Controller &);
    void getControllerReferences( TimeMngr *refTimeMngr, Nav *refNav);
    void initialize(void);
    void exec(void);

    double getControllerOutput(void)
    {
        return cmd;
    }
};

#endif