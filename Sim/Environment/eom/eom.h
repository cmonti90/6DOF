#ifndef EOM_H
#define EOM_H

#include "EOMEcef.h"
#include "mathlib.h"
#include "EomTypes.h"

class MassProperties;

class eom : public SimLib::EOMEcef
{
  public:

    eom( const double runRate, const std::string name = "eom" );
    virtual ~eom();

    // Getters
    double getAltitudeSeaLevel() const
    {
        return altSeaLevel_;
    }

    myMath::Vector3d getPosEcef() const
    {
        return posEcef_;
    }

    myMath::Vector3d getVelEcef() const
    {
        return velEcef_;
    }

    myMath::Vector3d getAccelEcef() const
    {
        return accelEcef_;
    }

    myMath::Vector3d getAngRatesBody() const
    {
        return angRatesBody_;
    }

  protected:

        enum : unsigned int
        {
            X = 0u,
            Y,
            Z
        };

        enum : unsigned int
        {
            ROLL = 0u,
            PITCH,
            YAW
        };

    void initialize() override;
    void update    () override;
    void finalize  () override;
    void requestReferences( SimLib::ReferenceRequest& refReq ) override;

    double t_;
    double t_prev_;
    int counter_;

    myMath::Vector3d forceEcef_;
    myMath::Vector3d specificForceEcef_;
    myMath::Vector3d momentEcef_;
    myMath::Vector3d gravityEcef_;

    myMath::Vector3d windVelBody_;

    myMath::AngleD eulerAngles_;

    myMath::Vector3d velBody_;
    myMath::Vector3d accelBody_;
    myMath::Vector3d angRatesBody_;
    myMath::Vector3d angAccelBody_;

    myMath::Vector3d posEcef_;
    myMath::Vector3d velEcef_;
    myMath::Vector3d accelEcef_;

    myMath::Vector3d posEci_;
    myMath::Vector3d velEci_;

    myMath::Vector3d posEnu_;
    myMath::Vector3d velEnu_;

    myMath::Vector3d posNed_;
    myMath::Vector3d velNed_;

    double flightPathAngle_;
    double angleOfAttack_;
    double angleOfAttackDot_;
    double angleOfSideslip_;
    double angleOfSideslipDot_;

    double lat_centric_;
    double lon_centric_;

    double lat_geodetic_;
    double lon_geodetic_;

    double earthRotation_;


    // Quaternions
    myMath::QuaternionD q_nedToBody_;
    myMath::QuaternionD q_ecefToNed_;
    myMath::QuaternionD q_ecefToEci_;
    myMath::QuaternionD q_ecefToBody_;
    myMath::QuaternionD q_eciToBody_;

    myMath::QuaternionD qdot_body_;


    // DCMs
    myMath::DCMd ecefFromEci_;
    myMath::DCMd bodyFromEcef_;
    myMath::DCMd bodyFromEci_;
    myMath::DCMd bodyFromNed_;
    myMath::DCMd bodyFromWind_;
    myMath::DCMd nedFromEcef_;
    myMath::DCMd enuFromEcef_;
    
    const myMath::DCMd enuFromNed_;

    myMath::Vector3d originEnuInEcef_;

    double altSeaLevel_;
    double altGeodetic_;

    myMath::QuaternionD quaternionDerivative( const double p, const double q, const double r, myMath::QuaternionD q0 );

    void updateEci();
    void updateNed();
    void updateBody();
    void updateAeroAngles();
    void updateWind();
    void updateStates();

    FILE* fEom_;
    bool logOutput_;

  private:

    MassProperties* pMassProps_;
};

#endif