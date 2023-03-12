#ifndef NAVIGATION_H
#define NAVIGATION_H

#include "TimeMngr.h"
#include "mathlib.h"
#include <iostream>

class Nav
{
protected:
    TimeMngr *pTimeMngr_;

    double time{0.0};
    double tk_1{0.0};

    myMath::Vector3d xbStates_{0.0};
    myMath::Vector<double, 6> xbdotdot_prev{0.0};
    myMath::Vector<double, 6> xbdot_prev{0.0};
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
    double Len{0.0};
    double I{0.0};
    double g{0.0};

    double Ff{0.0};
    double Mf{0.0};

    // Kalman Filter
    myMath::Vector3d u{0.0};
    myMath::Vector3d stateVec_k_k1{0.0};
    myMath::Vector3d stateVec_k1_k1{0.0};
    myMath::Vector3d yTilda{0.0};
    myMath::Vector3d z{1.0};

    myMath::Matrix3d kfF{0.0};
    myMath::Matrix3d kfB{0.0};
    myMath::Matrix3d kfS{0.0};
    myMath::Matrix3d kfK{0.0};
    myMath::Matrix3d kfQ{0.0};
    myMath::Matrix3d kfR{0.0};
    myMath::Matrix3d kfH{0.0};
    myMath::Matrix3d kfPk_k1{0.0};
    myMath::Matrix3d kfPk1_k1{0.0};

    // Extended Kalman Filter
    myMath::Vector4d ekfStateVec_tk_k{0.0};
    myMath::Vector4d ekfStateVec_tk_k1{0.0};
    myMath::Vector2d ekf_h{0.0};
    myMath::Vector2d ekfZ{0.0};
    myMath::Vector4d ekfF{0.0};
    myMath::Matrix4d ekfB{0.0};
    myMath::Matrix4d ekfPhi{0.0};
    myMath::Matrix<double, 4, 2> ekfK{0.0};
    myMath::Matrix4d ekfQ{0.0};
    myMath::Matrix4d ekfG{0.0};
    myMath::Matrix<double, 2, 4> ekfH{0.0};
    myMath::Matrix2d ekfR{0.0};
    myMath::Matrix4d ekfPtk_k{0.0};
    myMath::Matrix4d ekfPtk_k1{0.0};
    myMath::Matrix4d ekfPtk1_k1{0.0};

    // Unscented Kalman Filter

    int counter{0};

public:
    Nav(){};
    ~Nav();
    Nav(const Nav &obj);
    Nav &operator=(const Nav &);

    void getNavReferences(TimeMngr *x);
    void initialize(void);
    void exec(void);
    void setEncoderOutput(const double);
    void setImuOutput(const double, const double, const double);
    void Filter();
    void kalFilt();
    void extendedKalFilt();
    void unscentedKalFilt();
    myMath::Vector4d fVecEKF(myMath::Vector4d &stateVec);
    myMath::Vector2d hVecEKF(myMath::Vector4d &stateVec);
    myMath::Matrix4d AmatrixEKF(myMath::Vector4d &stateVec);
    myMath::Matrix<double, 2, 4> HmatrixEKF(myMath::Vector4d &stateVec);
    myMath::Matrix4d Phi(double t, double tau);
    myMath::Matrix4d integralTermEKF(double t0, double tf);

    myMath::Vector3d getxbStates(void)
    {
        myMath::Vector3d tmp;

        tmp[0] = xb;
        tmp[1] = xbdot;
        tmp[2] = xbdotdot;

        return tmp;
    };

    myMath::Vector3d getxrStates(void)
    {
        myMath::Vector3d tmp;

        tmp[0] = xr;
        tmp[1] = xrdot;
        tmp[2] = xrdotdot;

        return tmp;
    };

    myMath::Vector3d getthetaStates(void)
    {
        myMath::Vector3d tmp;

        tmp[0] = theta;
        tmp[1] = thetadot;
        tmp[2] = thetadotdot;

        return tmp;
    };
};

#endif