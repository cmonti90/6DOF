#ifndef AERO_H
#define AERO_H

#include "TimeMngr.h"
#include "mathlib.h"

class Aero
{
protected:

public:
    Aero();
    ~Aero();

    void initialize(void);
    void exec(void);
    void finalize(void);

protected:
    // Aerodynamic coefficients
    double C_D;
    double C_L;
    double C_Y;
    double C_l;
    double C_m;
    double C_n;

    // Aerodynamic forces
    double F_D;
    double F_L;
    double F_Y;

    // Aerodynamic moments
    double M_l;
    double M_m;
    double M_n;

    // Aerodynamic state variables
    double angleOfAttack;
    double angleOfSideslip;
    double bankAngle;

    // Aerodynamic state derivatives
    double angleOfAttackDot;
    double angleOfSideslipDot;
    double bankAngleDot;

    double velT;
    double dynamicPressure;
    double airDensity;
    double altSeaLevel;

    void updateCoefficients();
    void computeAeroForces();
    void computeAeroMoments();

private:
    Aero& operator=(const Aero& orig) = delete;
    Aero(const Aero& orig) = delete;
};

#endif /* AERO_H */