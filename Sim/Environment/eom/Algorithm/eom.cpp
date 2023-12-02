#include "eom.h"

#include "WGS84.h"
#include "PhysicalProperties.h"

#include "Units.h"

#include <math.h>
#include <iostream>


//////////////////////////////////////////////////////
/// @brief   Constructor
/// @param   None
/// @return  None
//////////////////////////////////////////////////////
eom::eom()
{
    if ( logOutput )
    {
        fEom = fopen( "eom.dat", "w" );
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
/// @brief   initialize EOM object
/// @param   None
/// @return  None
//////////////////////////////////////////////////////
void eom::initialize()
{
    dt = 1.0 / 1000.0;

    windVelBody = 0.0;
    naturalWindVelBody = 0.0;

    netForceBody = 0.0;
    netMomentBody = 0.0;

    posEci[0] = 5.0e3_km;
    posEci[1] = 5.0e3_km;
    posEci[2] = 5.0e3_km;

    velBody[0] = 0.0; // m/sec
    velBody[1] = 0.0;
    velBody[2] = 0.0;

    eulerAngles[0] = 0.0; // rad
    eulerAngles[1] = 0.0;
    eulerAngles[2] = 0.0;

    angRatesBody = 0.0; // rad/sec

    ecefFromEci = myMath::DCMd::Identity();

    enuFromNed[0][0] = 0.0;
    enuFromNed[0][1] = 1.0;
    enuFromNed[0][2] = 0.0;

    enuFromNed[1][0] = 1.0;
    enuFromNed[1][1] = 0.0;
    enuFromNed[1][2] = 0.0;

    enuFromNed[2][0] = 0.0;
    enuFromNed[2][1] = 0.0;
    enuFromNed[2][2] = -1.0;

    windVelBody = 0.0;

    q_nedToBody = myMath::QuaternionD::Identity();

    update();
}

//////////////////////////////////////////////////////
/// @note   Name: exec
/// @brief  Execution function to integrate the
///         equations of motion
/// @param  EOM input data structure
/// @param  EOM output data structure
/// @return None
//////////////////////////////////////////////////////
void eom::exec( const EomTypes::InData& inData, EomTypes::OutData& outData )
{
    t += dt;
    counter++;

    netForceBody = 0.0;
    netMomentBody = 0.0;

    rungeKutta4thOrder( inData );

    update();

    BuildOutput( outData );

    if ( logOutput )
    {
        myMath::QuaternionD qTest = eulerAngles.ToQuaternion( myMath::TaitBryanOrder::ZYX );
        fprintf( fEom, "%f, %f, %f, %f, %f, %f, %f, %f, %f, %f, %f, %f, %f, %f, %f, %f, %f, %f\n", t, posEci[0], posEci[1], posEci[2], eulerAngles[0], eulerAngles[1], eulerAngles[2]
                 , angRatesBody[0], angRatesBody[1], angRatesBody[2], q_nedToBody[0], q_nedToBody[1], q_nedToBody[2], q_nedToBody[3]
                 , qTest[0], qTest[1], qTest[2], qTest[3] );
    }

    netForceBody = 0.0;
    netMomentBody = 0.0;
    t_prev = t;

}

//////////////////////////////////////////////////////
/// @note   Name: finalize
/// @brief  Run at simulation end
/// @param  None
/// @return None
//////////////////////////////////////////////////////
void eom::finalize()
{
    if ( logOutput )
    {
        fclose( fEom );
    }
}

//////////////////////////////////////////////////////
/// @note   Name: BuildOutput
/// @brief  Pick out data for output
/// @param  EOM output data structure
/// @return None
//////////////////////////////////////////////////////
void eom::BuildOutput( EomTypes::OutData& outData )
{
    outData.windVelBody = windVelBody;
    outData.velBody = velBody;
    outData.accelBody = accelBody;

    outData.posEci = posEci;
    outData.velEci = velEci;

    outData.posEcef = posEcef;
    outData.velEcef = velEcef;

    outData.eulerAngs = eulerAngles;
    outData.eulerAngRates = angRatesBody;

    outData.angleOfAttack = angleOfAttack;
    outData.angleOfSideslip = angleOfSideslip;

    outData.bodyFromNed = bodyFromNed;
    outData.bodyFromWind = bodyFromWind;

    outData.altSeaLevel = altSeaLevel;
    outData.altGeodetic = altGeodetic;

    outData.lat = lat_geodetic;
    outData.lon = lon_geodetic;
}

//////////////////////////////////////////////////////
/// @note   Name: update
/// @brief  Update coordinate systems and states in
///         all coordinate systems
/// @param  None
/// @return None
//////////////////////////////////////////////////////
void eom::update()
{
    updateEcef();
    updateNed();
    updateBody();
    updateAeroAngles();
    updateWind();
    updateStates();
}

//////////////////////////////////////////////////////
/// @note   Name: updateStates
/// @brief  Update vehicle states in ECI, ECEF, ENU,
///         and NED coordinate systems
/// @param  None
/// @return None
//////////////////////////////////////////////////////
void eom::updateStates()
{
    velEci = bodyFromEci.Transpose() * velBody;

    velEcef = bodyFromEcef.Transpose() * velBody;

    posEnu = enuFromEcef * posEcef;
    velEnu = enuFromEcef * velEcef;

    posNed = enuFromNed * posEnu;
    velNed = enuFromNed * velEnu;
}

//////////////////////////////////////////////////////
/// @note   Name: updateStates
/// @brief  Implementation of the Rung-Kutta 4th order
///         integration method. Integration in done in
///         the body frame; the position delta in the
///         body frame is transformed to ECI and added
///         to the current ECI position.
/// @param  EOM input data structure
/// @return None
//////////////////////////////////////////////////////
void eom::rungeKutta4thOrder( const EomTypes::InData& inData )
{
    dt = 1.0 / 1000.0;

    myMath::Vector3d dPosBody[4];
    myMath::Vector3d dVelBody[4];

    myMath::Matrix4d Kq[4];
    myMath::Vector3d dAngBodyRates[4];
    myMath::Vector3d dAngBodyRatesDot;

    // Instantaneous accelerations
    accelBody[X]            = udot( velBody[Y], velBody[Z], angRatesBody[PITCH], angRatesBody[YAW], inData );
    accelBody[Y]            = vdot( velBody[X], velBody[Z], angRatesBody[ROLL], angRatesBody[YAW], inData );
    accelBody[Z]            = wdot( velBody[X], velBody[Y], angRatesBody[ROLL], angRatesBody[PITCH], inData );

    angAccelBody            = angularRatesDerivative( angRatesBody[ROLL], angRatesBody[PITCH], angRatesBody[YAW], inData );

    // k1
    dVelBody[0][X]          = dt * udot( velBody[Y], velBody[Z], angRatesBody[PITCH], angRatesBody[YAW], inData );
    dVelBody[0][Y]          = dt * vdot( velBody[X], velBody[Z], angRatesBody[ROLL], angRatesBody[YAW], inData );
    dVelBody[0][Z]          = dt * wdot( velBody[X], velBody[Y], angRatesBody[ROLL], angRatesBody[PITCH], inData );

    dPosBody[0][X]          = dt * velBody[X];
    dPosBody[0][Y]          = dt * velBody[Y];
    dPosBody[0][Z]          = dt * velBody[Z];

    dAngBodyRatesDot        = angularRatesDerivative( angRatesBody[ROLL], angRatesBody[PITCH], angRatesBody[YAW], inData );

    dAngBodyRates[0][ROLL]  = dt * dAngBodyRatesDot[ROLL];
    dAngBodyRates[0][PITCH] = dt * dAngBodyRatesDot[PITCH];
    dAngBodyRates[0][YAW]   = dt * dAngBodyRatesDot[YAW];

    qdot_body               = quaternionDerivative( angRatesBody[ROLL], angRatesBody[PITCH], angRatesBody[YAW], q_eciToBody );

    Kq[0]                   = QuaterionRKrotationMatrix( dt, 1.0 / 6.0, angRatesBody );


    // k2
    dVelBody[1][X]          = dt * udot( velBody[Y] + dVelBody[0][Y] / 2.0, velBody[Z] + dVelBody[0][Z] / 2.0, angRatesBody[PITCH] + dAngBodyRates[0][PITCH] / 2.0, angRatesBody[YAW]   + dAngBodyRates[0][YAW]   / 2.0, inData );
    dVelBody[1][Y]          = dt * vdot( velBody[X] + dVelBody[0][X] / 2.0, velBody[Z] + dVelBody[0][Z] / 2.0, angRatesBody[ROLL]  + dAngBodyRates[0][ROLL]  / 2.0, angRatesBody[YAW]   + dAngBodyRates[0][YAW]   / 2.0, inData );
    dVelBody[1][Z]          = dt * wdot( velBody[X] + dVelBody[0][X] / 2.0, velBody[Y] + dVelBody[0][Y] / 2.0, angRatesBody[ROLL]  + dAngBodyRates[0][ROLL]  / 2.0, angRatesBody[PITCH] + dAngBodyRates[0][PITCH] / 2.0, inData );

    dPosBody[1][X]          = dt * ( velBody[X] + dVelBody[0][X] / 2.0 );
    dPosBody[1][Y]          = dt * ( velBody[Y] + dVelBody[0][Y] / 2.0 );
    dPosBody[1][Z]          = dt * ( velBody[Z] + dVelBody[0][Z] / 2.0 );

    dAngBodyRatesDot        = angularRatesDerivative( angRatesBody[ROLL] + dAngBodyRates[0][ROLL] / 2.0, angRatesBody[PITCH] + dAngBodyRates[0][PITCH] / 2.0, angRatesBody[YAW] + dAngBodyRates[0][YAW] / 2.0, inData );

    dAngBodyRates[1][ROLL]  = dt * dAngBodyRatesDot[ROLL];
    dAngBodyRates[1][PITCH] = dt * dAngBodyRatesDot[PITCH];
    dAngBodyRates[1][YAW]   = dt * dAngBodyRatesDot[YAW];

    Kq[1]                   = QuaterionRKrotationMatrix( dt, 1.0 / 3.0, angRatesBody );

    // k3
    dVelBody[2][X]          = dt * udot( velBody[Y] + dVelBody[1][Y] / 2.0, velBody[Z] + dVelBody[1][Z] / 2.0, angRatesBody[PITCH] + dAngBodyRates[1][PITCH] / 2.0, angRatesBody[YAW]   + dAngBodyRates[1][YAW]   / 2.0, inData );
    dVelBody[2][Y]          = dt * vdot( velBody[X] + dVelBody[1][X] / 2.0, velBody[Z] + dVelBody[1][Z] / 2.0, angRatesBody[ROLL]  + dAngBodyRates[1][ROLL]  / 2.0, angRatesBody[YAW]   + dAngBodyRates[1][YAW]   / 2.0, inData );
    dVelBody[2][Z]          = dt * wdot( velBody[X] + dVelBody[1][X] / 2.0, velBody[Y] + dVelBody[1][Y] / 2.0, angRatesBody[ROLL]  + dAngBodyRates[1][ROLL]  / 2.0, angRatesBody[PITCH] + dAngBodyRates[1][PITCH] / 2.0, inData );

    dPosBody[2][X]          = dt * ( velBody[X] + dVelBody[1][X] / 2.0 );
    dPosBody[2][Y]          = dt * ( velBody[Y] + dVelBody[1][Y] / 2.0 );
    dPosBody[2][Z]          = dt * ( velBody[Z] + dVelBody[1][Z] / 2.0 );

    dAngBodyRatesDot        = angularRatesDerivative( angRatesBody[ROLL] + dAngBodyRates[1][ROLL] / 2.0, angRatesBody[PITCH] + dAngBodyRates[1][PITCH] / 2.0, angRatesBody[YAW] + dAngBodyRates[1][YAW] / 2.0, inData );

    dAngBodyRates[2][ROLL]  = dt * dAngBodyRatesDot[ROLL];
    dAngBodyRates[2][PITCH] = dt * dAngBodyRatesDot[PITCH];
    dAngBodyRates[2][YAW]   = dt * dAngBodyRatesDot[YAW];

    Kq[2]                   = QuaterionRKrotationMatrix( dt, 1.0 / 3.0, angRatesBody );

    // k4
    dVelBody[3][X]          = dt * udot( velBody[Y] + dVelBody[2][Y], velBody[Z] + dVelBody[2][Z], angRatesBody[PITCH] + dAngBodyRates[2][PITCH], angRatesBody[YAW]   + dAngBodyRates[2][YAW], inData );
    dVelBody[3][Y]          = dt * vdot( velBody[X] + dVelBody[2][X], velBody[Z] + dVelBody[2][Z], angRatesBody[ROLL]  + dAngBodyRates[2][ROLL], angRatesBody[YAW]   + dAngBodyRates[2][YAW], inData );
    dVelBody[3][Z]          = dt * wdot( velBody[X] + dVelBody[2][X], velBody[Y] + dVelBody[2][Y], angRatesBody[ROLL]  + dAngBodyRates[2][ROLL], angRatesBody[PITCH] + dAngBodyRates[2][PITCH], inData );

    dPosBody[3][X]          = dt * ( velBody[X] + dVelBody[2][X] );
    dPosBody[3][Y]          = dt * ( velBody[Y] + dVelBody[2][Y] );
    dPosBody[3][Z]          = dt * ( velBody[Z] + dVelBody[2][Z] );

    dAngBodyRatesDot        = angularRatesDerivative( angRatesBody[ROLL] + dAngBodyRates[2][ROLL], angRatesBody[PITCH] + dAngBodyRates[2][PITCH], angRatesBody[YAW] + dAngBodyRates[2][YAW], inData );

    dAngBodyRates[3][ROLL]  = dt * dAngBodyRatesDot[ROLL];
    dAngBodyRates[3][PITCH] = dt * dAngBodyRatesDot[PITCH];
    dAngBodyRates[3][YAW]   = dt * dAngBodyRatesDot[YAW];

    Kq[3]                   = QuaterionRKrotationMatrix( dt, 1.0 / 6.0, angRatesBody );


    // Update state
    velBody[X]          += ( dVelBody[0][X] + 2.0 * ( dVelBody[1][X] + dVelBody[2][X] ) + dVelBody[3][X] ) / 6.0;
    velBody[Y]          += ( dVelBody[0][Y] + 2.0 * ( dVelBody[1][Y] + dVelBody[2][Y] ) + dVelBody[3][Y] ) / 6.0;
    velBody[Z]          += ( dVelBody[0][Z] + 2.0 * ( dVelBody[1][Z] + dVelBody[2][Z] ) + dVelBody[3][Z] ) / 6.0;

    myMath::Vector3d deltaPosBody;
    deltaPosBody[X]     = ( dPosBody[0][X] + 2.0 * ( dPosBody[1][X] + dPosBody[2][X] ) + dPosBody[3][X] ) / 6.0;
    deltaPosBody[Y]     = ( dPosBody[0][Y] + 2.0 * ( dPosBody[1][Y] + dPosBody[2][Y] ) + dPosBody[3][Y] ) / 6.0;
    deltaPosBody[Z]     = ( dPosBody[0][Z] + 2.0 * ( dPosBody[1][Z] + dPosBody[2][Z] ) + dPosBody[3][Z] ) / 6.0;

    posEci              += bodyFromEci.Transpose() * deltaPosBody;

    q_nedToBody         = Kq[3] * Kq[2] * Kq[1] * Kq[0] * q_nedToBody;
    q_nedToBody.Normalize();

    angRatesBody[ROLL]  += ( dAngBodyRates[0][ROLL]   + 2.0 * ( dAngBodyRates[1][ROLL]  + dAngBodyRates[2][ROLL]  ) + dAngBodyRates[3][ROLL]  ) / 6.0;
    angRatesBody[PITCH] += ( dAngBodyRates[0][PITCH]  + 2.0 * ( dAngBodyRates[1][PITCH] + dAngBodyRates[2][PITCH] ) + dAngBodyRates[3][PITCH] ) / 6.0;
    angRatesBody[YAW]   += ( dAngBodyRates[0][YAW]    + 2.0 * ( dAngBodyRates[1][YAW]   + dAngBodyRates[2][YAW]   ) + dAngBodyRates[3][YAW]   ) / 6.0;

    eulerAngles = q_nedToBody.Inverse().ToEuler( myMath::TaitBryanOrder::ZYX );
}

//////////////////////////////////////////////////////
/// @note   Name: updateEcef
/// @brief  Update ECEF frame and states
/// @param  None
/// @return None
//////////////////////////////////////////////////////
void eom::updateEcef()
{
    earthRotation   += myMath::Constants::EARTH_ROTATION_RATE * dt;

    double cosW     = std::cos( earthRotation );
    double sinW     = std::sin( earthRotation );

    ecefFromEci[0][0] = cosW;
    ecefFromEci[0][1] = sinW;
    ecefFromEci[0][2] = 0.0;

    ecefFromEci[1][0] = -sinW;
    ecefFromEci[1][1] = cosW;
    ecefFromEci[1][2] = 0.0;

    ecefFromEci[2][0] = 0.0;
    ecefFromEci[2][1] = 0.0;
    ecefFromEci[2][2] = 1.0;

    q_ecefToEci = ecefFromEci.Transpose().ToQuaternion();

    posEcef     = ecefFromEci * posEci;

    altSeaLevel = posEcef.Magnitude() - myMath::Constants::EARTH_SEALEVEL_RADIUS;
}

//////////////////////////////////////////////////////
/// @note   Name: updateNed
/// @brief  Update NED frame and states
/// @param  None
/// @return None
//////////////////////////////////////////////////////
void eom::updateNed()
{
    lat_centric = std::atan2( posEcef[Z], posEcef[X] );
    lon_centric = std::atan2( posEcef[Y], posEcef[X] );

    lon_geodetic = lon_centric;

    WGS84::EcefToLla( posEcef, lat_geodetic, lon_geodetic, altGeodetic );

    double cosLat = std::cos( lat_geodetic );
    double sinLat = std::sin( lat_geodetic );
    double cosLon = std::cos( lon_geodetic );
    double sinLon = std::sin( lon_geodetic );

    enuFromEcef[0][0] = -sinLon;
    enuFromEcef[0][1] = cosLon;
    enuFromEcef[0][2] = 0.0;

    enuFromEcef[1][0] = -sinLat * cosLon;
    enuFromEcef[1][1] = -sinLat * sinLon;
    enuFromEcef[1][2] = cosLat;

    enuFromEcef[2][0] = cosLat * cosLon;
    enuFromEcef[2][1] = cosLat * sinLon;
    enuFromEcef[2][2] = sinLat;

    nedFromEcef = enuFromNed.Transpose() * enuFromEcef;
}

//////////////////////////////////////////////////////
/// @note   Name: updateBody
/// @brief  Update body frame and states
/// @param  None
/// @return None
//////////////////////////////////////////////////////
void eom::updateBody()
{
    bodyFromNed  = eulerAngles.ToDCM( myMath::TaitBryanOrder::ZYX );

    bodyFromEcef = bodyFromNed * nedFromEcef;

    bodyFromEci  = bodyFromEcef * ecefFromEci;
}

//////////////////////////////////////////////////////
/// @note   Name: updateAeroAngles
/// @brief  Update aerodynamic angles
/// @param  None
/// @return None
//////////////////////////////////////////////////////
void eom::updateAeroAngles()
{
    angleOfAttack   = std::atan2( velBody[Z], velBody[X] ) + Aircraft::WingIncidenceAngle;
    angleOfSideslip = std::asin( velBody[Y] / velBody.Magnitude() );

    angleOfAttackDot    = ( std::cos( angleOfSideslip ) * accelBody[X] + std::sin( angleOfSideslip ) * accelBody[Z] ) / velBody.Magnitude();
    angleOfSideslipDot  = ( accelBody[Y] - angleOfAttackDot * velBody[Y] ) / velBody.Magnitude();

    flightPathAngle = eulerAngles[PITCH] - angleOfAttack;

    angleOfAttackTotal          = std::acos( velBody[X] / velBody.Magnitude() );
    angleOfAttackTotalClockAng  = std::atan2( velBody[Y], velBody[Z] );
}

//////////////////////////////////////////////////////
/// @note   Name: updateWind
/// @brief  Update wind frame and states
/// @param  None
/// @return None
//////////////////////////////////////////////////////
void eom::updateWind()
{
    windVelBody = -velBody + naturalWindVelBody;

    double cosAoA  = std::cos( angleOfAttack );
    double sinAoA  = std::sin( angleOfAttack );
    double cosAoSS = std::cos( angleOfSideslip );
    double sinAoSS = std::sin( angleOfSideslip );

    bodyFromWind[0][0] = cosAoA * cosAoSS;
    bodyFromWind[0][1] = sinAoSS;
    bodyFromWind[0][2] = sinAoA * cosAoSS;

    bodyFromWind[1][0] = -cosAoA * sinAoSS;
    bodyFromWind[1][1] = cosAoSS;
    bodyFromWind[1][2] = -sinAoA * sinAoSS;

    bodyFromWind[2][0] = -sinAoA;
    bodyFromWind[2][1] = 0.0;
    bodyFromWind[2][2] = cosAoA;
}

//////////////////////////////////////////////////////
/// @note   Name: udot
/// @brief  Calculate the acceleration in the X
///         direction in the body frame
/// @param  Y velocity in body frame
/// @param  Z velocity in body frame
/// @param  Pitch rate in body frame
/// @param  Yaw rate in body frame
/// @param  EOM input data structure
/// @return Acceleration in X direction in body frame
//////////////////////////////////////////////////////
double eom::udot( const double v, const double w, const double q, const double r, const EomTypes::InData& inData )
{
    return ( r * v - q * w ) + netForceBody[X] / inData.mass;
}

//////////////////////////////////////////////////////
/// @note   Name: vdot
/// @brief  Calculate the acceleration in the Y
///         direction in the body frame
/// @param  X velocity in body frame
/// @param  Z velocity in body frame
/// @param  Roll rate in body frame
/// @param  Yaw rate in body frame
/// @param  EOM input data structure
/// @return Acceleration in Y direction in body frame
//////////////////////////////////////////////////////
double eom::vdot( const double u, const double w, const double p, const double r, const EomTypes::InData& inData )
{
    return ( p * w - r * u ) + netForceBody[Y] / inData.mass;
}

//////////////////////////////////////////////////////
/// @note   Name: wdot
/// @brief  Calculate the acceleration in the Z
///         direction in the body frame
/// @param  X velocity in body frame
/// @param  Y velocity in body frame
/// @param  Roll rate in body frame
/// @param  Pitch rate in body frame
/// @param  EOM input data structure
/// @return Acceleration in Z direction in body frame
//////////////////////////////////////////////////////
double eom::wdot( const double u, const double v, const double p, const double q, const EomTypes::InData& inData )
{
    return ( q * u - p * v ) + netForceBody[Z] / inData.mass;
}

//////////////////////////////////////////////////////
/// @note   Name: angularRatesDerivative
/// @brief  Calculate the angular acceleration in
///         the body frame
/// @param  Roll rate in body frame
/// @param  Pitch rate in body frame
/// @param  Yaw rate in body frame
/// @param  EOM input data structure
/// @return Acceleration in Z direction in body frame
//////////////////////////////////////////////////////
myMath::Vector3d eom::angularRatesDerivative( const double p, const double q, const double r, const EomTypes::InData& inData )
{
    myMath::Vector3d angularRatesDerivs;

    angularRatesDerivs[ROLL]  = -q * ( -p * inData.I[X][Z] - q * inData.I[Y][Z] + r * inData.I[Z][Z] ) + r * ( -p * inData.I[X][Y] + q * inData.I[Y][Y] - r * inData.I[Y][Z] ) + netMomentBody[ROLL];
    angularRatesDerivs[PITCH] =  p * ( -p * inData.I[X][Z] - q * inData.I[Y][Z] + r * inData.I[Z][Z] ) - r * (  p * inData.I[X][X] - q * inData.I[X][Y] + r * inData.I[X][Z] ) + netMomentBody[PITCH];
    angularRatesDerivs[YAW]   = -p * ( -p * inData.I[X][Y] + q * inData.I[Y][Y] - r * inData.I[Y][Z] ) + q * (  p * inData.I[X][X] - q * inData.I[X][Y] + r * inData.I[X][Z] ) + netMomentBody[YAW];

    return inData.I.Inverse() * angularRatesDerivs;
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

//////////////////////////////////////////////////////
/// @note   Name: QuaterionRKrotationMatrix
/// @brief  Calculate rotor derivative using
///         angular rates for Runge-Kutta
/// @param  Time step
/// @param  Integration scalar
/// @param  Rotation rates
/// @return Rotor
//////////////////////////////////////////////////////
myMath::Matrix4d eom::QuaterionRKrotationMatrix( const double dt, const double scalar, const myMath::Vector3d& rotRates )
{
    if ( myMath::isZero( rotRates.Magnitude() ) )
    {
        return myMath::Matrix4d::Identity();
    }

    myMath::Matrix4d omega;
    omega[0][0] = 0.0;
    omega[0][1] = -rotRates[2];
    omega[0][2] = rotRates[1];
    omega[0][3] = rotRates[0];

    omega[1][0] = rotRates[2];
    omega[1][1] = 0.0;
    omega[1][2] = -rotRates[0];
    omega[1][3] = rotRates[1];

    omega[2][0] = -rotRates[1];
    omega[2][1] = rotRates[0];
    omega[2][2] = 0.0;
    omega[2][3] = rotRates[2];

    omega[3][0] = -rotRates[0];
    omega[3][1] = -rotRates[1];
    omega[3][2] = -rotRates[2];
    omega[3][3] = 0.0;

    myMath::Matrix4d rotation = myMath::Matrix4d::Identity() * std::cos( 0.5 * dt * scalar * rotRates.Magnitude() )
                                + omega * std::sin( 0.5 * dt * scalar * rotRates.Magnitude() ) / rotRates.Magnitude();

    return rotation;
}

//////////////////////////////////////////////////////
/// @note   Name: addForces
/// @brief  Add forces to the net force
/// @param  Force in body frame
/// @return None
//////////////////////////////////////////////////////
void eom::addForces( const myMath::Vector3d& force )
{
    netForceBody += force;
}

//////////////////////////////////////////////////////
/// @note   Name: addMoments
/// @brief  Add moments to the net force
/// @param  Moment in body frame
/// @return None
//////////////////////////////////////////////////////
void eom::addMoments( const myMath::Vector3d& moment )
{
    netMomentBody += moment;
}