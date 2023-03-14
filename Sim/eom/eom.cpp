#include "eom.h"

#include <math.h>

eom::eom()
{
}

void eom::getEomReferences(TimeMngr *refTimeMngr)
{
    pTimeMngr = refTimeMngr;
}

void eom::initialize(void)
{
    xbdotdot_ = 0.0;
    xbdot_ = 0.0;
    xb_ = 0.0;

    xrdotdot = 0.0;
    xrdot = 0.0;
    xr = 0.0;

    thetadotdot_ = 0.0;
    thetadot_ = 0.0;
    theta_ = 60.0 * myMath::Constants::PI / 180.0;

    mb = 3.0;
    mr = 2.0;
    I = 3.0;
    Frg = mr * myMath::Constants::GRAVITY_ACCEL;
    Len = 0.5;

    Ff = 0.0;
    Ff_mag = 0.0;
    Mf = 0.0;
    Mf_mag = 0.0;

    motorAccel = 0.0;

    dt = 0.0001;
    t = 0.0;
    counter = 0;

    mass = 75.0;
    Atrans = mass * myMath::Matrix3d().Identity();
    Atrans_inv = (1.0 / mass) * myMath::Matrix3d().Identity();
    Btrans = myMath::Matrix3d().Identity();

    I = 10.0;
    Arot = I * myMath::Matrix3d().Identity();
    Arot_inv = (1.0 / I) * myMath::Matrix3d().Identity();
    Arot = myMath::Matrix3d().Identity();



    // printf("thetadotdot = %f\t thetadot = %f\t theta = %f\t", thetadotdot_, thetadot_, theta_);
}

void eom::exec(void)
{
    t += dt;
    counter++;

    setMotorDynamics();

    rungeKutta4thOrder();

    if (counter % 1000 == 0)
    {
        // printf("thetadotdot = %f\t thetadot = %f\t theta = %f", thetadotdot_, thetadot_, theta_);
        // printf("theta = %f\t", theta_);
    }
}

void eom::rungeKutta4thOrder(void)
{
    

    //////////////////////////////////////////////////

    double dXbdot1;
    double dXbdot2;
    double dXbdot3;
    double dXbdot4;
    double dXb1;
    double dXb2;
    double dXb3;
    double dXb4;
    double dThetaDot1;
    double dThetaDot2;
    double dThetaDot3;
    double dThetaDot4;
    double dTheta1;
    double dTheta2;
    double dTheta3;
    double dTheta4;

    dXbdot1 = dt * xbDotDotOde(theta_, thetadot_);
    dXb1 = dt * xbdot_;
    dThetaDot1 = dt * thetaDotDotOde(theta_, thetadot_);
    dTheta1 = dt * thetadot_;

    dXbdot2 = dt * xbDotDotOde(theta_ + dTheta1 / 2.0, thetadot_ + dThetaDot1 / 2.0);
    dXb2 = dt * (xbdot_ + dXb1 / 2.0);
    dThetaDot2 = dt * thetaDotDotOde(theta_ + dTheta1 / 2.0, thetadot_ + dThetaDot1 / 2.0);
    dTheta2 = dt * (thetadot_ + dTheta1 / 2.0);

    dXbdot3 = dt * xbDotDotOde(theta_ + dTheta2 / 2.0, thetadot_ + dThetaDot2 / 2.0);
    dXb3 = dt * (xbdot_ + dXb2 / 2.0);
    dThetaDot3 = dt * thetaDotDotOde(theta_ + dTheta2 / 2.0, thetadot_ + dThetaDot2 / 2.0);
    dTheta3 = dt * (thetadot_ + dTheta2 / 2.0);

    dXbdot4 = dt * xbDotDotOde(theta_ + dTheta3, thetadot_ + dThetaDot3);
    dXb4 = dt * (xbdot_ + dXb3);
    dThetaDot4 = dt * thetaDotDotOde(theta_ + dTheta3, thetadot_ + dThetaDot3);
    dTheta4 = dt * (thetadot_ + dTheta3);

    xbdotdot_ = xbDotDotOde(theta_, thetadot_);
    xbdot_ += (dXbdot1 + 2.0 * dXbdot2 + 2.0 * dXbdot3 + dXbdot4) / 6.0;
    xb_ += (dXb1 + 2.0 * dXb2 + 2.0 * dXb3 + dXb4) / 6.0;

    thetadotdot_ = thetaDotDotOde(theta_, thetadot_);
    thetadot_ += (dThetaDot1 + 2.0 * dThetaDot2 + 2.0 * dThetaDot3 + dThetaDot4) / 6.0;
    theta_ += (dTheta1 + 2.0 * dTheta2 + 2.0 * dTheta3 + dTheta4) / 6.0;

    if (theta_ > 2.0 * myMath::Constants::PI)
    {
        theta_ -= 2.0 * myMath::Constants::PI * std::floor(theta_ / (2.0 * myMath::Constants::PI));
    }
    else if (theta_ <= 2.0 * myMath::Constants::PI)
    {
        theta_ -= 2.0 * myMath::Constants::PI * std::floor(theta_ / (2.0 * myMath::Constants::PI));
    }
}

double eom::thetaDotDotOde(double theta, double thetadot)
{
    

    return ((std::pow(mr * Len * thetadot, 2) * std::cos(theta) + mr * Len * Ff + (mb + mr) * Mf - (mb + mr) * mr * myMath::Constants::GRAVITY_ACCEL * Len * std::cos(theta)) / ((mb + mr) * (I + mr * std::pow(Len, 2) - std::pow(mr * Len, 2) * std::sin(theta) / (mb + mr))));
}

double eom::xbDotDotOde(double theta, double thetadot)
{
    return ((mr * Len * (thetaDotDotOde(theta, thetadot) * std::sin(theta) - myMath::SQ(thetadot) * std::cos(theta)) + Ff + motorAccel) / (mb + mr));
}

void eom::setMotorDynamics(void)
{
}