#ifndef EOM_H
#define EOM_H

#include "mathlib.h"
#include "EomTypes.h"

class eom
{
public:
    eom();
    ~eom();

    void initialize(void);
    void exec(const EomTypes::InData &inData, EomTypes::OutData &outData);
    void finalize(void);

    // Setters
    void addForces(const myMath::Vector3d &force);
    void addMoments(const myMath::Vector3d &moment);

protected:
    void BuildOutput(EomTypes::OutData &outData);

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

    double dt{0.0};
    double t{0.0};
    double t_prev{0.0};
    int counter{0};

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

    myMath::Vector3d dPosEci;

    myMath::Vector3d posEci;
    myMath::Vector3d velEci;

    myMath::Vector3d posEcef;
    myMath::Vector3d velEcef;

    myMath::Vector3d posEnu;
    myMath::Vector3d velEnu;

    myMath::Vector3d posNed;
    myMath::Vector3d velNed;

    double flightPathAngle;
    double angleOfAttackTotal;
    double angleOfAttackTotalClockAng;
    double angleOfAttack;
    double angleOfAttackDot;
    double angleOfSideslip;
    double angleOfSideslipDot;

    double lat_centric;
    double lon_centric;

    double lat_geodetic;
    double lon_geodetic;

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
    double altGeodetic;

    double udot(const double v, const double w, const double q, const double r, const EomTypes::InData &inData);
    double vdot(const double u, const double w, const double p, const double r, const EomTypes::InData &inData);
    double wdot(const double u, const double v, const double p, const double q, const EomTypes::InData &inData);

    myMath::Vector3d angularRatesDerivative(const double p, const double q, const double r, const EomTypes::InData &inData);

    void rungeKutta4thOrder(const EomTypes::InData &inData);

    void update();
    void updateEcef();
    void updateNed();
    void updateBody();
    void updateAeroAngles();
    void updateWind();
    void updateStates();
};

#endif