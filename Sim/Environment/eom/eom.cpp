#include "eom.h"
#include "MassProperties.h"

#include "WGS84.h"
#include "PhysicalProperties.h"

#include "Units.h"

#include "SimTime.h"

#include <math.h>
#include <iostream>


//////////////////////////////////////////////////////
/// @brief   Constructor
/// @param   None
/// @return  None
//////////////////////////////////////////////////////
eom::eom( const double runRate, const std::string name )
    : EOMEcef( runRate, name )
    , t_( 0.0 )
    , t_prev_( 0.0 )
    , counter_( 0 )

    , forceEcef_( 0.0 )
    , specificForceEcef_( 0.0 )
    , momentEcef_( 0.0 )
    , gravityEcef_( 0.0 )

    , windVelBody_( 0.0 )

    , eulerAngles_( 0.0 )

    , velBody_( 0.0 )
    , accelBody_( 0.0 )
    , angRatesBody_( 0.0 )
    , angAccelBody_( 0.0 )

    , posEcef_( 0.0 )
    , velEcef_( 0.0 )
    , accelEcef_( 0.0 )

    , posEci_( 0.0 )
    , velEci_( 0.0 )

    , posEnu_( 0.0 )
    , velEnu_( 0.0 )

    , posNed_( 0.0 )
    , velNed_( 0.0 )

    , flightPathAngle_( 0.0 )
    , angleOfAttack_( 0.0 )
    , angleOfSideslip_( 0.0 )
    , angleOfAttackDot_( 0.0 )
    , angleOfSideslipDot_( 0.0 )

    , lat_centric_( 0.0 )
    , lon_centric_( 0.0 )

    , lat_geodetic_( 0.0 )
    , lon_geodetic_( 0.0 )

    , earthRotation_( 0.0 )

    , q_nedToBody_()
    , q_ecefToNed_()
    , q_ecefToEci_()
    , q_ecefToBody_()
    , q_eciToBody_()

    , qdot_body_()

    , ecefFromEci_( 0.0 )
    , bodyFromEcef_( 0.0 )
    , bodyFromEci_( 0.0 )
    , bodyFromNed_( 0.0 )
    , bodyFromWind_( 0.0 )
    , nedFromEcef_( 0.0 )
    , enuFromEcef_( 0.0 )

    , enuFromNed_( { 0.0, 1.0, 0.0,
    1.0, 0.0, 0.0,
    0.0, 0.0, -1.0 } )

, originEnuInEcef_( 0.0 )

, altSeaLevel_( 0.0 )

, fEom_( nullptr )
, logOutput_( true )

, pMassProps_( nullptr )
{
    if ( logOutput_ )
    {
        fEom_ = fopen( "eom.dat", "w" );
    }
}


//////////////////////////////////////////////////////
/// @brief   Destructor
/// @param   None
/// @return  None
//////////////////////////////////////////////////////
eom::~eom()
{
}


//////////////////////////////////////////////////////
/// @brief   requestReferences
/// @param   None
/// @return  None
//////////////////////////////////////////////////////
void eom::requestReferences( SimLib::ReferenceRequest& refReq )
{
    SimLib::EOMEcef::requestReferences( refReq );

    refReq.requestReference( reinterpret_cast< SimLib::Model** >( &pMassProps_ ), "MassProperties" );
}

//////////////////////////////////////////////////////
/// @note    Name: initialize
/// @brief   initialize EOM object
/// @param   None
/// @return  None
//////////////////////////////////////////////////////
void eom::initialize()
{
    windVelBody_ = 0.0;

    // posEcef_[0] = 5.0e3_km; // m
    // posEcef_[1] = 5.0e3_km; // m
    // posEcef_[2] = 5.0e3_km; // m

    WGS84::LlaToEcef( 0.0, 0.0, 1000.0, posEcef_ );
    

    velEcef_[0] = 0.0; // m/sec
    velEcef_[1] = 0.0;
    velEcef_[2] = 0.0;

    eulerAngles_[0] = 0.0; // rad
    eulerAngles_[1] = 0.0;
    eulerAngles_[2] = 0.0;

    angRatesBody_ = 0.0; // rad/sec

    ecefFromEci_ = myMath::DCMd::Identity();

    windVelBody_ = 0.0;

    q_nedToBody_ = myMath::QuaternionD::Identity();

    altSeaLevel_ = 0.0;

    update();
}


//////////////////////////////////////////////////////
/// @note   Name: update
/// @brief  Integrate the equations of motion and
///         update coordinate systems and states in
///         all coordinate systems
/// @param  None
/// @return None
//////////////////////////////////////////////////////
void eom::update()
{
    t_ = SimLib::SimTime::GetInstance()->getTimeNow();

    forceEcef_          = m_forceEffector->getForce();
    // specificForceEcef_  = forceEcef_ / pMassProps_->getMass();
    specificForceEcef_  = 0.0;
    momentEcef_         = m_forceEffector->getMoment();

    RungeKutta4thOrder( posEcef_, velEcef_, accelEcef_, angRatesBody_, angAccelBody_, pMassProps_->getRotInertia(),
                        q_nedToBody_, specificForceEcef_, momentEcef_ );

    UpdateEci();
    UpdateNed();
    UpdateBody();
    UpdateAeroAngles();
    UpdateWind();

    if ( logOutput_ )
    {
        fprintf( fEom_, "%f, %f, %f, %f, %f, %f, %f, %f, %f, %f, %f, %f, %f, %f, %f, %f, %f, %f, %f, %f, %f, %f, %f, %f\n", t_,
                 posEcef_[0], posEcef_[1], posEcef_[2], velEcef_[0], velEcef_[1], velEcef_[2], accelEcef_[0], accelEcef_[1], accelEcef_[2],
                 eulerAngles_[0], eulerAngles_[1], eulerAngles_[2], angRatesBody_[0], angRatesBody_[1], angRatesBody_[2],
                 q_nedToBody_[0], q_nedToBody_[1], q_nedToBody_[2], q_nedToBody_[3] );
    }

    t_prev_ = t_;
    counter_++;
}


//////////////////////////////////////////////////////
/// @note   Name: finalize
/// @brief  Run at simulation end
/// @param  None
/// @return None
//////////////////////////////////////////////////////
void eom::finalize()
{
    if ( logOutput_ )
    {
        fclose( fEom_ );
    }
}


//////////////////////////////////////////////////////
/// @note   Name: UpdateEci
/// @brief  Update ECI frame and states
/// @param  None
/// @return None
//////////////////////////////////////////////////////
void eom::UpdateEci()
{
    earthRotation_   += myMath::Constants::EARTH_ROTATION_RATE / m_rate;

    double cosW     = std::cos( earthRotation_ );
    double sinW     = std::sin( earthRotation_ );

    ecefFromEci_[0][0] = cosW;
    ecefFromEci_[0][1] = sinW;
    ecefFromEci_[0][2] = 0.0;

    ecefFromEci_[1][0] = -sinW;
    ecefFromEci_[1][1] = cosW;
    ecefFromEci_[1][2] = 0.0;

    ecefFromEci_[2][0] = 0.0;
    ecefFromEci_[2][1] = 0.0;
    ecefFromEci_[2][2] = 1.0;

    q_ecefToEci_ = myMath::Transpose( ecefFromEci_ ).ToQuaternion();

    posEci_     = myMath::Transpose( ecefFromEci_ ) * posEcef_;
    velEci_     = myMath::Transpose( ecefFromEci_ ) * posEcef_;

    altSeaLevel_ = posEcef_.Magnitude() - myMath::Constants::EARTH_SEALEVEL_RADIUS;
}


//////////////////////////////////////////////////////
/// @note   Name: UpdateNed
/// @brief  Update NED frame and states
/// @param  None
/// @return None
//////////////////////////////////////////////////////
void eom::UpdateNed()
{
    lat_centric_ = std::atan2( posEcef_[Z], posEcef_[X] );
    lon_centric_ = std::atan2( posEcef_[Y], posEcef_[X] );

    lon_geodetic_ = lon_centric_;

    WGS84::EcefToLla( posEcef_, lat_geodetic_, lon_geodetic_, altGeodetic_ );

    double cosLat = std::cos( lat_geodetic_ );
    double sinLat = std::sin( lat_geodetic_ );
    double cosLon = std::cos( lon_geodetic_ );
    double sinLon = std::sin( lon_geodetic_ );

    enuFromEcef_[0][0] = -sinLon;
    enuFromEcef_[0][1] = cosLon;
    enuFromEcef_[0][2] = 0.0;

    enuFromEcef_[1][0] = -sinLat * cosLon;
    enuFromEcef_[1][1] = -sinLat * sinLon;
    enuFromEcef_[1][2] = cosLat;

    enuFromEcef_[2][0] = cosLat * cosLon;
    enuFromEcef_[2][1] = cosLat * sinLon;
    enuFromEcef_[2][2] = sinLat;

    nedFromEcef_ = myMath::Transpose( enuFromNed_ ) * enuFromEcef_;

    posEnu_ = enuFromEcef_ * posEcef_;
    velEnu_ = enuFromEcef_ * velEcef_;

    posNed_ = myMath::Transpose( enuFromNed_ ) * posEnu_;
    velNed_ = myMath::Transpose( enuFromNed_ ) * velEnu_;
}


//////////////////////////////////////////////////////
/// @note   Name: UpdateBody
/// @brief  Update body frame and states
/// @param  None
/// @return None
//////////////////////////////////////////////////////
void eom::UpdateBody()
{
    bodyFromNed_  = eulerAngles_.ToDCM( myMath::TaitBryanOrder::ZYX );
    bodyFromEcef_ = bodyFromNed_ * nedFromEcef_;
    bodyFromEci_  = bodyFromEcef_ * ecefFromEci_;


}


//////////////////////////////////////////////////////
/// @note   Name: UpdateAeroAngles
/// @brief  Update aerodynamic angles
/// @param  None
/// @return None
//////////////////////////////////////////////////////
void eom::UpdateAeroAngles()
{
    angleOfAttack_   = std::atan2( velBody_[Z], velBody_[X] ) + Aircraft::WingIncidenceAngle;
    angleOfSideslip_ = std::asin( velBody_[Y] / velBody_.Magnitude() );

    angleOfAttackDot_    = ( std::cos( angleOfSideslip_ ) * accelBody_[X] + std::sin( angleOfSideslip_ ) * accelBody_[Z] ) / velBody_.Magnitude();
    angleOfSideslipDot_  = ( accelBody_[Y] - angleOfAttackDot_ * velBody_[Y] ) / velBody_.Magnitude();

    flightPathAngle_ = eulerAngles_[PITCH] - angleOfAttack_;
}


//////////////////////////////////////////////////////
/// @note   Name: UpdateWind
/// @brief  Update wind frame and states
/// @param  None
/// @return None
//////////////////////////////////////////////////////
void eom::UpdateWind()
{
    windVelBody_ = -velBody_;

    double cosAoA  = std::cos( angleOfAttack_ );
    double sinAoA  = std::sin( angleOfAttack_ );
    double cosAoSS = std::cos( angleOfSideslip_ );
    double sinAoSS = std::sin( angleOfSideslip_ );

    bodyFromWind_[0][0] = cosAoA * cosAoSS;
    bodyFromWind_[0][1] = sinAoSS;
    bodyFromWind_[0][2] = sinAoA * cosAoSS;

    bodyFromWind_[1][0] = -cosAoA * sinAoSS;
    bodyFromWind_[1][1] = cosAoSS;
    bodyFromWind_[1][2] = -sinAoA * sinAoSS;

    bodyFromWind_[2][0] = -sinAoA;
    bodyFromWind_[2][1] = 0.0;
    bodyFromWind_[2][2] = cosAoA;
}

//////////////////////////////////////////////////////
/// @note   Name: quaternionDerivative
/// @brief  Calculate quaternion derivative using
///         angular rates
/// @param  Roll rate in body frame
/// @param  Pitch rate in body frame
/// @param  Yaw rate in body frame
/// @param  Quaternion from any frame to body frame
/// @return Quaternion derivative
//////////////////////////////////////////////////////
myMath::QuaternionD eom::quaternionDerivative( const double p, const double q, const double r, myMath::QuaternionD q0 )
{
    q0.Normalize();

    myMath::Matrix4d omega;

    omega[0][0] = 0.0;
    omega[0][1] = -r;
    omega[0][2] = q;
    omega[0][3] = p;

    omega[1][0] = r;
    omega[1][1] = 0.0;
    omega[1][2] = -p;
    omega[1][3] = q;

    omega[2][0] = -q;
    omega[2][1] = p;
    omega[2][2] = 0.0;
    omega[2][3] = r;

    omega[3][0] = -p;
    omega[3][1] = -q;
    omega[3][2] = -r;
    omega[3][3] = 0.0;

    myMath::QuaternionD q_out = 0.5 * omega * q0;

    return q_out;
}
