#ifndef AERO_H
#define AERO_H

#include "Model.h"
#include "mathlib.h"

class eom;
class EarthGRAM;
// class ControlSurfaces;

class Aero : public SimLib::Model
{

  public:
    Aero( const double runRate, const std::string name = "Aero" );
    virtual ~Aero();

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

    void updateCoefficients();
    void updateWingCoefficients();
    void updateFuselageCoefficients();
    void updateHorizontalTailCoefficients();
    void updateVerticalTailCoefficients();
    void updateAileronCoefficients();
    void updateElevatorCoefficients();
    void updateRudderCoefficients();
    void computeAeroForces();
    void computeAeroMoments();


  private:


    void initialize() override;
    void update() override;
    void finalize() override;

    virtual void getReferenceRequest( SimLib::ReferenceRequest& refReq ) override;

    virtual SimLib::ReferenceRequest requestReferences() const override;

    eom* pEom_;
    EarthGRAM* pEarthGRAM_;
    // ControlSurfaces* pControlSurfaces_;

    Aero& operator=( const Aero& orig ) = delete;
    Aero( const Aero& orig ) = delete;
};

#endif /* AERO_H */