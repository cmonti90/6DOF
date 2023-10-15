#include "eom.h"

#include "WGS84.h"
#include "PhysicalProperties.h"

#include "Units.h"

#include <math.h>
#include <iostream>

eom::eom()
{
    if ( logOutput )
    {
        fEom = fopen( "eom.dat", "w" );
    }
}

eom::~eom()
{
}

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
        myMath::QuaternionD qTest = eulerAngles.ToQuaternion(myMath::TaitBryanOrder::ZYX);
        fprintf( fEom, "%f, %f, %f, %f, %f, %f, %f, %f, %f, %f, %f, %f, %f, %f, %f, %f, %f, %f\n", t, posEci[0], posEci[1], posEci[2], eulerAngles[0], eulerAngles[1], eulerAngles[2]
                 , angRatesBody[0], angRatesBody[1], angRatesBody[2], q_nedToBody[0], q_nedToBody[1], q_nedToBody[2], q_nedToBody[3]
                 , qTest[0], qTest[1], qTest[2], qTest[3] );
    }

    netForceBody = 0.0;
    netMomentBody = 0.0;
    t_prev = t;

}

void eom::finalize()
{
    if ( logOutput )
    {
        fclose( fEom );
    }
}

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

void eom::update()
{
    updateEcef();
    updateNed();
    updateBody();
    updateAeroAngles();
    updateWind();
    updateStates();
}

void eom::updateStates()
{
    velEci = bodyFromEci.Transpose() * velBody;

    velEcef = bodyFromEcef.Transpose() * velBody;

    posEnu = enuFromEcef * posEcef;
    velEnu = enuFromEcef * velEcef;

    posNed = enuFromNed * posEnu;
    velNed = enuFromNed * velEnu;
}

void eom::rungeKutta4thOrder( const EomTypes::InData& inData )
{
    double dXdot1;
    double dXdot2;
    double dXdot3;
    double dXdot4;
    double dX1;
    double dX2;
    double dX3;
    double dX4;

    double dYdot1;
    double dYdot2;
    double dYdot3;
    double dYdot4;
    double dY1;
    double dY2;
    double dY3;
    double dY4;

    double dZdot1;
    double dZdot2;
    double dZdot3;
    double dZdot4;
    double dZ1;
    double dZ2;
    double dZ3;
    double dZ4;

    myMath::Matrix4d Kq1;
    myMath::Matrix4d Kq2;
    myMath::Matrix4d Kq3;
    myMath::Matrix4d Kq4;

    myMath::Vector3d dAngBodyRates1;
    myMath::Vector3d dAngBodyRates2;
    myMath::Vector3d dAngBodyRates3;
    myMath::Vector3d dAngBodyRates4;

    myMath::Vector3d dAngBodyRates;

    velBody[X] = 10.0;
    velBody[Y] = 10.0;
    velBody[Z] = 10.0;

    angRatesBody[0] = -50.0 * myMath::Constants::DEG_TO_RAD;
    angRatesBody[1] = 10.0 * myMath::Constants::DEG_TO_RAD;
    angRatesBody[2] = 15.0 * myMath::Constants::DEG_TO_RAD;

    dt = 1.0 / 1000.0;

    accelBody[X] = udot( velBody[Y], velBody[Z], angRatesBody[PITCH], angRatesBody[YAW], inData );
    accelBody[Y] = vdot( velBody[X], velBody[Z], angRatesBody[ROLL], angRatesBody[YAW], inData );
    accelBody[Z] = wdot( velBody[X], velBody[Y], angRatesBody[ROLL], angRatesBody[PITCH], inData );

    angAccelBody = angularRatesDerivative( angRatesBody[0], angRatesBody[1], angRatesBody[2], inData );


    // k1
    dXdot1  = dt * udot( velBody[Y], velBody[Z], angRatesBody[PITCH], angRatesBody[YAW], inData );
    dYdot1  = dt * vdot( velBody[X], velBody[Z], angRatesBody[ROLL], angRatesBody[YAW], inData );
    dZdot1  = dt * wdot( velBody[X], velBody[Y], angRatesBody[ROLL], angRatesBody[PITCH], inData );

    dX1     = dt * velBody[X];
    dY1     = dt * velBody[Y];
    dZ1     = dt * velBody[Z];

    dAngBodyRates = angularRatesDerivative( angRatesBody[0], angRatesBody[1], angRatesBody[2], inData );

    dAngBodyRates1[0]   = dt * dAngBodyRates[ROLL];
    dAngBodyRates1[1]   = dt * dAngBodyRates[PITCH];
    dAngBodyRates1[2]   = dt * dAngBodyRates[YAW];

    qdot_body   = quaternionDerivative( angRatesBody[0], angRatesBody[1], angRatesBody[2], q_eciToBody );

    Kq1 = QuaterionRKrotationMatrix( dt, 1.0 / 6.0, angRatesBody );


    // k2
    dXdot2  = dt * udot( velBody[Y] + dYdot1 / 2.0, velBody[Z] + dZdot1 / 2.0, angRatesBody[PITCH] + dAngBodyRates1[1] / 2.0, angRatesBody[YAW] + dAngBodyRates1[2] / 2.0, inData );
    dYdot2  = dt * vdot( velBody[X] + dXdot1 / 2.0, velBody[Z] + dZdot1 / 2.0, angRatesBody[ROLL] + dAngBodyRates1[0] / 2.0, angRatesBody[YAW] + dAngBodyRates1[2] / 2.0, inData  );
    dZdot2  = dt * wdot( velBody[X] + dXdot1 / 2.0, velBody[Y] + dYdot1 / 2.0, angRatesBody[ROLL] + dAngBodyRates1[0] / 2.0, angRatesBody[PITCH] + dAngBodyRates1[1] / 2.0, inData );

    dX2     = dt * ( velBody[X] + dX1 / 2.0 );
    dY2     = dt * ( velBody[Y] + dY1 / 2.0 );
    dZ2     = dt * ( velBody[Z] + dZ1 / 2.0 );

    dAngBodyRates = angularRatesDerivative( angRatesBody[ROLL] + dAngBodyRates1[0] / 2.0, angRatesBody[PITCH] + dAngBodyRates1[1] / 2.0, angRatesBody[YAW] + dAngBodyRates1[2] / 2.0, inData );

    dAngBodyRates2[0]   = dt * dAngBodyRates[ROLL];
    dAngBodyRates2[1]   = dt * dAngBodyRates[PITCH];
    dAngBodyRates2[2]   = dt * dAngBodyRates[YAW];

    Kq2 = QuaterionRKrotationMatrix( dt, 1.0 / 3.0, angRatesBody );

    // k3
    dXdot3  = dt * udot( velBody[Y] + dYdot2 / 2.0, velBody[Z] + dZdot2 / 2.0, angRatesBody[PITCH] + dAngBodyRates2[1] / 2.0, angRatesBody[YAW] + dAngBodyRates2[2] / 2.0, inData );
    dYdot3  = dt * vdot( velBody[X] + dXdot2 / 2.0, velBody[Z] + dZdot2 / 2.0, angRatesBody[ROLL] + dAngBodyRates2[0] / 2.0, angRatesBody[YAW] + dAngBodyRates2[2] / 2.0, inData );
    dZdot3  = dt * wdot( velBody[X] + dXdot2 / 2.0, velBody[Y] + dYdot2 / 2.0, angRatesBody[ROLL] + dAngBodyRates2[0] / 2.0, angRatesBody[PITCH] + dAngBodyRates2[1] / 2.0, inData );

    dX3     = dt * ( velBody[X] + dX2 / 2.0 );
    dY3     = dt * ( velBody[Y] + dY2 / 2.0 );
    dZ3     = dt * ( velBody[Z] + dZ2 / 2.0 );

    dAngBodyRates = angularRatesDerivative( angRatesBody[ROLL] + dAngBodyRates2[0] / 2.0, angRatesBody[PITCH] + dAngBodyRates2[1] / 2.0, angRatesBody[YAW] + dAngBodyRates2[2] / 2.0, inData );

    dAngBodyRates3[0]   = dt * dAngBodyRates[ROLL];
    dAngBodyRates3[1]   = dt * dAngBodyRates[PITCH];
    dAngBodyRates3[2]   = dt * dAngBodyRates[YAW];

    Kq3 = QuaterionRKrotationMatrix( dt, 1.0 / 3.0, angRatesBody );

    // k4
    dXdot4  = dt * udot( velBody[Y] + dYdot3, velBody[Z] + dZdot3, angRatesBody[PITCH] + dAngBodyRates3[1], angRatesBody[YAW] + dAngBodyRates3[2], inData );
    dYdot4  = dt * vdot( velBody[X] + dXdot3, velBody[Z] + dZdot3, angRatesBody[ROLL] + dAngBodyRates3[0], angRatesBody[YAW] + dAngBodyRates3[2], inData );
    dZdot4  = dt * wdot( velBody[X] + dXdot3, velBody[Y] + dYdot3, angRatesBody[ROLL] + dAngBodyRates3[0], angRatesBody[PITCH] + dAngBodyRates3[1], inData );

    dX4     = dt * ( velBody[X] + dX3 );
    dY4     = dt * ( velBody[Y] + dY3 );
    dZ4     = dt * ( velBody[Z] + dZ3 );

    dAngBodyRates = angularRatesDerivative( angRatesBody[ROLL] + dAngBodyRates3[0], angRatesBody[PITCH] + dAngBodyRates3[1], angRatesBody[YAW] + dAngBodyRates3[2], inData );

    dAngBodyRates4[0]   = dt * dAngBodyRates[ROLL];
    dAngBodyRates4[1]   = dt * dAngBodyRates[PITCH];
    dAngBodyRates4[2]   = dt * dAngBodyRates[YAW];

    Kq4 = QuaterionRKrotationMatrix( dt, 1.0 / 6.0, angRatesBody );


    // Update state
    velBody[X] += ( dXdot1 + 2.0 * dXdot2 + 2.0 * dXdot3 + dXdot4 ) / 6.0;
    velBody[Y] += ( dYdot1 + 2.0 * dYdot2 + 2.0 * dYdot3 + dYdot4 ) / 6.0;
    velBody[Z] += ( dZdot1 + 2.0 * dZdot2 + 2.0 * dZdot3 + dZdot4 ) / 6.0;

    myMath::Vector3d dPosBody;
    dPosBody[X] = ( dX1 + 2.0 * dX2 + 2.0 * dX3 + dX4 ) / 6.0;
    dPosBody[Y] = ( dY1 + 2.0 * dY2 + 2.0 * dY3 + dY4 ) / 6.0;
    dPosBody[Z] = ( dZ1 + 2.0 * dZ2 + 2.0 * dZ3 + dZ4 ) / 6.0;

    posEci += bodyFromEci.Transpose() * dPosBody;

    q_nedToBody = Kq4 * Kq3 * Kq2 * Kq1 * q_nedToBody;
    q_nedToBody.Normalize();

    angRatesBody[ROLL]  += ( dAngBodyRates1[0] + 2.0 * dAngBodyRates2[0] + 2.0 * dAngBodyRates3[0] + dAngBodyRates4[0] ) / 6.0;
    angRatesBody[PITCH] += ( dAngBodyRates1[1] + 2.0 * dAngBodyRates2[1] + 2.0 * dAngBodyRates3[1] + dAngBodyRates4[1] ) / 6.0;
    angRatesBody[YAW]   += ( dAngBodyRates1[2] + 2.0 * dAngBodyRates2[2] + 2.0 * dAngBodyRates3[2] + dAngBodyRates4[2] ) / 6.0;

    eulerAngles = q_nedToBody.Inverse().ToEuler( myMath::TaitBryanOrder::ZYX );
}

void eom::updateEcef()
{
    earthRotation   += myMath::Constants::EARTH_ROTATION_RATE * dt;

    ecefFromEci[0][0] = std::cos( earthRotation );
    ecefFromEci[0][1] = std::sin( earthRotation );
    ecefFromEci[0][2] = 0.0;

    ecefFromEci[1][0] = -std::sin( earthRotation );
    ecefFromEci[1][1] = std::cos( earthRotation );
    ecefFromEci[1][2] = 0.0;

    ecefFromEci[2][0] = 0.0;
    ecefFromEci[2][1] = 0.0;
    ecefFromEci[2][2] = 1.0;

    q_ecefToEci = ecefFromEci.Transpose().ToQuaternion();

    posEcef = ecefFromEci * posEci;

    altSeaLevel = posEcef.Magnitude() - myMath::Constants::EARTH_SEALEVEL_RADIUS;
}

void eom::updateNed()
{
    lat_centric = std::atan2( posEcef[Z], posEcef[X] );
    lon_centric = std::atan2( posEcef[Y], posEcef[X] );

    lon_geodetic = lon_centric;

    WGS84::EcefToLla( posEcef, lat_geodetic, lon_geodetic, altGeodetic );

    enuFromEcef[0][0] = -std::sin( lon_geodetic );
    enuFromEcef[0][1] = std::cos( lon_geodetic );
    enuFromEcef[0][2] = 0.0;

    enuFromEcef[1][0] = -std::sin( lat_geodetic ) * std::cos( lon_geodetic );
    enuFromEcef[1][1] = -std::sin( lat_geodetic ) * std::sin( lon_geodetic );
    enuFromEcef[1][2] = std::cos( lat_geodetic );

    enuFromEcef[2][0] = std::cos( lat_geodetic ) * std::cos( lon_geodetic );
    enuFromEcef[2][1] = std::cos( lat_geodetic ) * std::sin( lon_geodetic );
    enuFromEcef[2][2] = std::sin( lat_geodetic );

    nedFromEcef = enuFromNed.Transpose() * enuFromEcef;
}

void eom::updateBody()
{
    bodyFromNed = eulerAngles.ToDCM( myMath::TaitBryanOrder::ZYX );

    bodyFromEcef = bodyFromNed * nedFromEcef;

    bodyFromEci = bodyFromEcef * ecefFromEci;
}

void eom::updateAeroAngles()
{
    angleOfAttack = std::atan2( velBody[Z], velBody[X] ) + Aircraft::WingIncidenceAngle;
    angleOfSideslip = std::asin( velBody[Y] / velBody.Magnitude() );

    angleOfAttackDot = ( std::cos( angleOfSideslip ) * accelBody[X] + std::sin( angleOfSideslip ) * accelBody[Z] ) / velBody.Magnitude();
    angleOfSideslipDot = ( accelBody[Y] - angleOfAttackDot * velBody[Y] ) / velBody.Magnitude();

    flightPathAngle = eulerAngles[PITCH] - angleOfAttack;

    angleOfAttackTotal = std::acos( velBody[X] / velBody.Magnitude() );
    angleOfAttackTotalClockAng = std::atan2( velBody[Y], velBody[Z] );
}

void eom::updateWind()
{
    windVelBody = -velBody + naturalWindVelBody;

    bodyFromWind[0][0] = std::cos( angleOfAttack ) * std::cos( angleOfSideslip );
    bodyFromWind[0][1] = std::sin( angleOfSideslip );
    bodyFromWind[0][2] = std::sin( angleOfAttack ) * std::cos( angleOfSideslip );

    bodyFromWind[1][0] = -std::cos( angleOfAttack ) * std::sin( angleOfSideslip );
    bodyFromWind[1][1] = std::cos( angleOfSideslip );
    bodyFromWind[1][2] = -std::sin( angleOfAttack ) * std::sin( angleOfSideslip );

    bodyFromWind[2][0] = -std::sin( angleOfAttack );
    bodyFromWind[2][1] = 0.0;
    bodyFromWind[2][2] = std::cos( angleOfAttack );
}

double eom::udot( const double v, const double w, const double q, const double r, const EomTypes::InData& inData )
{
    return ( r * v - q * w ) + ( 1.0 / inData.mass ) * ( netForceBody[X] );
}

double eom::vdot( const double u, const double w, const double p, const double r, const EomTypes::InData& inData )
{
    return ( p * w - r * u ) + ( 1.0 / inData.mass ) * ( netForceBody[Y] );
}

double eom::wdot( const double u, const double v, const double p, const double q, const EomTypes::InData& inData )
{
    return ( q * u - p * v ) + ( 1.0 / inData.mass ) * ( netForceBody[Z] );
}

myMath::Vector3d eom::angularRatesDerivative( const double p, const double q, const double r, const EomTypes::InData& inData )
{
    myMath::Vector3d angularRatesDerivs;

    angularRatesDerivs[ROLL] = -q * ( -p * inData.I[X][Z] - q * inData.I[Y][Z] + r * inData.I[Z][Z] ) + r * ( -p * inData.I[X][Y] + q * inData.I[Y][Y] - r * inData.I[Y][Z] ) + netMomentBody[ROLL];
    angularRatesDerivs[PITCH] = p * ( -p * inData.I[X][Z] - q * inData.I[Y][Z] + r * inData.I[Z][Z] ) - r * ( p * inData.I[X][X] - q * inData.I[X][Y] + r * inData.I[X][Z] ) + netMomentBody[PITCH];
    angularRatesDerivs[YAW] = -p * ( -p * inData.I[X][Y] + q * inData.I[Y][Y] - r * inData.I[Y][Z] ) + q * ( p * inData.I[X][X] - q * inData.I[X][Y] + r * inData.I[X][Z] ) + netMomentBody[YAW];

    return inData.I.Inverse() * angularRatesDerivs;
}

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
    // q_out.Normalize();

    return q_out;
}

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
                                + omega * std::sin( 0.5 * dt * scalar * rotRates.Magnitude() ) / rotRates.Magnitude(); // + omega * omega * (1.0 - std::cos(0.5 * dt * scalar * rotRates.Magnitude())) / (rotRates.Magnitude() * rotRates.Magnitude());

    return rotation;
}

void eom::addForces( const myMath::Vector3d& force )
{
    netForceBody += force;
}

void eom::addMoments( const myMath::Vector3d& moment )
{
    netMomentBody += moment;
}