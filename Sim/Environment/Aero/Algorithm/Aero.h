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

    struct Coef
    {
        double C_D;
        double C_D0;
        double C_Dalpha;
        double C_DalphaDot;
        double C_Dq;

        double C_L;
        double C_L0;
        double C_Lalpha;
        double C_LalphaDot;
        double C_Lq;

        double C_Y;
        double C_Y0;
        double C_Ybeta;
        double C_YbetaDot;
        double C_Yp;
        double C_Yr;

        double C_l;
        double C_l0;
        double C_lbeta;
        double C_lbetaDot;
        double C_lp;
        double C_lr;

        double C_m;
        double C_m0;
        double C_malpha;
        double C_malphaDot;
        double C_mq;

        double C_n;
        double C_n0;
        double C_nbeta;
        double C_nbetaDot;
        double C_np;
        double C_nr;
    };

    // Aerodynamic coefficients

    Coef wing;
    Coef fuselage;
    Coef horzTail;
    Coef vertTail;
    Coef ail;
    Coef elev;
    Coef rudder;

    Coef aeroCoefs;

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
    double altSeaLevel;
    double mach;

    void updateCoefficients(const AeroTypes::InData& inData);
    void updateWingCoefficients(const AeroTypes::InData& inData);
    void updateFuselageCoefficients(const AeroTypes::InData& inData);
    void updateHorizontalTailCoefficients(const AeroTypes::InData& inData);
    void updateVerticalTailCoefficients(const AeroTypes::InData& inData);
    void updateAileronCoefficients(const AeroTypes::InData& inData);
    void updateElevatorCoefficients(const AeroTypes::InData& inData);
    void updateRudderCoefficients(const AeroTypes::InData& inData);
    void computeAeroForces();
    void computeAeroMoments();

    void BuildOutput(AeroTypes::OutData& outData);

private:
    Aero& operator=(const Aero& orig) = delete;
    Aero(const Aero& orig) = delete;
};

#endif /* AERO_H */