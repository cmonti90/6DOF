#ifndef EOM_H
#define EOM_H

#include <iostream>
#include <array>
#include "TimeMngr.h"
#include "mathlib.h"

class eom
{
protected:
    TimeMngr *pTimeMngr;

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

    double mass;
    myMath::Matrix3d I;

    myMath::Vector3d transStateVecDot;
    myMath::Vector3d transStateVec;

    myMath::Matrix3d Atrans;
    myMath::Matrix3d Atrans_inv;
    myMath::Matrix3d Btrans;

    myMath::Vector3d rotStateVecDot;
    myMath::Vector3d rotStateVec;

    myMath::Matrix3d Arot;
    myMath::Matrix3d Arot_inv;
    myMath::Matrix3d Brot;
    double mb{0.0};
    double mr{0.0};
    double Len{0.0};

    double Frg{0.0};
    double Ff{0.0};
    double Ff_mag{0.0};
    double Mf{0.0};
    double Mf_mag{0.0};

    void getMotorOutput(void);
    void rungeKutta4thOrder(void);
    myMath::Vector<myMath::Vector3d, 2> stateEquation(const myMath::Matrix3d transMat, const myMath::Matrix3d rotMat, const myMath::Vector3d transVec, const myMath::Vector3d rotVec);
    double thetaDotDotOde(double xbdotdot, double theta);
    double xbDotDotOde(double xbdotdot, double theta);

public:
    eom();
    ~eom() = default;
    eom(const eom &obj);
    eom &operator=(const eom &obj);
    void getEomReferences(TimeMngr *refTimeMngr);
    void initialize(void);
    void exec(void);

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