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

    double C_Dw;
    double C_Lw;
    double C_Yw;
    double C_lw;
    double C_mw;
    double C_nw;

    double C_Df;
    double C_Lf;
    double C_Yf;
    double C_lf;
    double C_mf;
    double C_nf;

    double C_Dht;
    double C_Lht;
    double C_Yht;
    double C_lht;
    double C_mht;
    double C_nht;

    double C_Dvt;
    double C_Lvt;
    double C_Yvt;
    double C_lvt;
    double C_mvt;
    double C_nvt;

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
    double speedOfSound;
    double airTempK;
    double mach;

    void updateCoefficients(const AeroTypes::InData& inData);
    void updateWingCoefficients(const AeroTypes::InData& inData);
    void updateFuselageCoefficients(const AeroTypes::InData& inData);
    void updateHorizontalTailCoefficients(const AeroTypes::InData& inData);
    void updateVerticalTailCoefficients(const AeroTypes::InData& inData);
    void computeAeroForces();
    void computeAeroMoments();

    void BuildOutput(AeroTypes::OutData& outData);

private:
    Aero& operator=(const Aero& orig) = delete;
    Aero(const Aero& orig) = delete;
};

#endif /* AERO_H */