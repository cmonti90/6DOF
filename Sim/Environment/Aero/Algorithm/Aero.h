#ifndef AERO_H
#define AERO_H

#include "mathlib.h"
#include "AeroTypes.h"

class Aero
{
protected:

public:
    Aero();
    ~Aero();

    void initialize(void);
    void exec(const AeroTypes::InData& inData, AeroTypes::OutData& outData);
    void finalize(void);

protected:

    myMath::Vector3d aeroForceBody;
    myMath::Vector3d aeroMomentBody;

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

    void BuildOutput(AeroTypes::OutData& outData);

private:
    Aero& operator=(const Aero& orig) = delete;
    Aero(const Aero& orig) = delete;
};

#endif /* AERO_H */