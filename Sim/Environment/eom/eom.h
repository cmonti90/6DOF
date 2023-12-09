#ifndef EOM_H
#define EOM_H

#include "Model.h"
#include "mathlib.h"
#include "EomTypes.h"

class eom : public SimLib::Model
{
    public:
        eom( const double runRate, const std::string name = "eom" );
        virtual ~eom();

        // Getters
        double getAltitudeSeaLevel() const
        {
            return altSeaLevel;
        }

    protected:

        void initialize ( void ) override;
        void update     ()       override;
        void finalize   ( void ) override;

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

        myMath::AngleD eulerAngles;
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

        double earthRotation;


        // Quaternions
        myMath::QuaternionD q_nedToBody;
        myMath::QuaternionD q_ecefToNed;
        myMath::QuaternionD q_ecefToEci;
        myMath::QuaternionD q_ecefToBody;
        myMath::QuaternionD q_eciToBody;

        myMath::QuaternionD qdot_body;


        // DCMs
        myMath::DCMd ecefFromEci;
        myMath::DCMd bodyFromEcef;
        myMath::DCMd bodyFromEci;
        myMath::DCMd bodyFromNed;
        myMath::DCMd bodyFromWind;
        myMath::DCMd nedFromEcef;
        myMath::DCMd enuFromNed;
        myMath::DCMd enuFromEcef;

        myMath::Vector3d originEnuInEcef;

        double altSeaLevel;
        double altGeodetic;

        double udot ( const double v, const double w, const double q, const double r );
        double vdot ( const double u, const double w, const double p, const double r );
        double wdot ( const double u, const double v, const double p, const double q );

        myMath::Vector3d angularRatesDerivative ( const double p, const double q, const double r );
        myMath::QuaternionD quaternionDerivative ( const double p, const double q, const double r, myMath::QuaternionD q0 );

        myMath::Matrix4d QuaterionRKrotationMatrix (const double dt, const double scalar, const myMath::Vector3d& rotRates);

        void rungeKutta4thOrder();

        void updateEcef();
        void updateNed();
        void updateBody();
        void updateAeroAngles();
        void updateWind();
        void updateStates();

        FILE* fEom;
        bool logOutput{true};
};

#endif