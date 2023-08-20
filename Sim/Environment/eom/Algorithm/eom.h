#ifndef EOM_H
#define EOM_H

#include "TimeMngr.h"
#include "mathlib.h"

class eom
{
public:
    eom();
    ~eom();

    void initialize(void);
    void exec(void);
    void finalize(void);

    // Setters
    void addForces(const myMath::Vector3d &force);
    void addMoments(const myMath::Vector3d &moment);

protected:
    enum : unsigned int
    {
        X,
        Y,
        Z
    };

    enum : unsigned int
    {
        ROLL,
        PITCH,
        YAW
    };

    TimeMngr *pTimeMngr;

    double dt{0.0};
    double t{0.0};
    double t_prev{0.0};
    int counter{0};

    double mass;
    myMath::Matrix3d I;

    myMath::Vector3d windVelBody;
    double naturalWindVelBody;

    //

    myMath::Vector3d netForceBody;
    myMath::Vector3d netMomentBody;

    myMath::Vector3d eulerAngles;
    myMath::Vector3d velBody;
    myMath::Vector3d accelBody;
    myMath::Vector3d angRatesBody;
    myMath::Vector3d angAccelBody;

    myMath::Vector3d posEcef;
    myMath::Vector3d velEcef;

    myMath::Vector3d posEci;
    myMath::Vector3d velEci;

    myMath::Vector3d posEnu;
    myMath::Vector3d velEnu;

    myMath::Vector3d posNed;
    myMath::Vector3d velNed;

    double flightPathAngle;
    double angleOfAttackTotal;
    double angleOfAttackTotalClockAng;
    double angleOfAttack;
    double angleOfSideslip;

    double lat_centric;
    double lon_centric;

    double lat_detic;
    double lon_detic;

    double phi;
    double theta;
    double psi;

    double earthRotation;

    // DCMs
    myMath::Matrix3d ecefFromEci;
    myMath::Matrix3d bodyFromEcef;
    myMath::Matrix3d bodyFromEci;
    myMath::Matrix3d bodyFromNed;
    myMath::Matrix3d bodyFromWind;
    myMath::Matrix3d nedFromEcef;
    myMath::Matrix3d enuFromNed;
    myMath::Matrix3d enuFromEcef;

    double altSeaLevel;

    double udot(const double v, const double w, const double q, const double r);
    double vdot(const double u, const double w, const double p, const double r);
    double wdot(const double u, const double v, const double p, const double q);

    myMath::Vector3d angularRatesDerivative(const double p, const double q, const double r);

    void rungeKutta4thOrder();
    void updateDCMs();
    void updateStates();
};

#endif