#include "eom.h"

#include "PhysicalProperties.h"

#include <math.h>

eom::eom()
{
}

eom::~eom()
{
}

void eom::initialize()
{
    mass = 3000.0;

    I = 0.0;
    I[0][0] = 50.0;  // Ixx
    I[1][1] = 250.0; // Iyy
    I[2][2] = 250.0; // Izz

    ecefFromEci = myMath::Matrix3d::Identity();

    enuFromNed[0][0] = 0.0;
    enuFromNed[0][1] = 1.0;
    enuFromNed[0][2] = 0.0;

    enuFromNed[1][0] = 1.0;
    enuFromNed[1][1] = 0.0;
    enuFromNed[1][2] = 0.0;

    enuFromNed[2][0] = 0.0;
    enuFromNed[2][1] = 0.0;
    enuFromNed[2][2] = -1.0;
}

void eom::exec()
{
    dt = t - t_prev;
    t += dt;
    counter++;

    rungeKutta4thOrder();
    updateDCMs();
    updateStates();

    if (counter % 1000 == 0)
    {
        // printf("thetadotdot = %f\t thetadot = %f\t theta = %f", thetadotdot_, thetadot_, theta_);
        // printf("theta = %f\t", theta_);
    }

    netForceBody = 0.0;
    netMomentBody = 0.0;
    t_prev = t;
}

void eom::updateStates()
{
    velEci = bodyFromEci.Transpose() * velBody;

    posEcef = ecefFromEci * posEci;
    velEcef = bodyFromEcef.Transpose() * velBody;

    posNed = enuFromNed * posEcef;
    velNed = enuFromNed * velEcef;
}

void eom::rungeKutta4thOrder()
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

    double dPhiDot1;
    double dPhiDot2;
    double dPhiDot3;
    double dPhiDot4;
    double dPhi1;
    double dPhi2;
    double dPhi3;
    double dPhi4;

    double dThetaDot1;
    double dThetaDot2;
    double dThetaDot3;
    double dThetaDot4;
    double dTheta1;
    double dTheta2;
    double dTheta3;
    double dTheta4;

    double dPsiDot1;
    double dPsiDot2;
    double dPsiDot3;
    double dPsiDot4;
    double dPsi1;
    double dPsi2;
    double dPsi3;
    double dPsi4;

    myMath::Vector3d dEulerAngRates;

    accelBody[X] = udot(velBody[Y], velBody[Z], angRatesBody[PITCH], angRatesBody[YAW]);
    accelBody[Y] = vdot(velBody[X], velBody[Z], angRatesBody[ROLL], angRatesBody[YAW]);
    accelBody[Z] = wdot(velBody[X], velBody[Y], angRatesBody[ROLL], angRatesBody[PITCH]);

    angAccelBody = angularRatesDerivative(angRatesBody[0], angRatesBody[1], angRatesBody[2]);

    // k1
    dXdot1 = dt * udot(velBody[Y], velBody[Z], angRatesBody[PITCH], angRatesBody[YAW]);
    dX1 = dt * velBody[X];
    dYdot1 = dt * vdot(velBody[X], velBody[Z], angRatesBody[ROLL], angRatesBody[YAW]);
    dY1 = dt * velBody[Y];
    dZdot1 = dt * wdot(velBody[X], velBody[Y], angRatesBody[ROLL], angRatesBody[PITCH]);
    dZ1 = dt * velBody[Z];

    dEulerAngRates = angularRatesDerivative(angRatesBody[0], angRatesBody[1], angRatesBody[2]);

    dPhiDot1 = dt * dEulerAngRates[ROLL];
    dPhi1 = dt * angRatesBody[ROLL];
    dThetaDot1 = dt * dEulerAngRates[PITCH];
    dTheta1 = dt * angRatesBody[PITCH];
    dPsiDot1 = dt * dEulerAngRates[YAW];
    dPsi1 = dt * angRatesBody[YAW];


    // k2
    dXdot2 = dt * udot(velBody[Y] + dYdot1 / 2.0, velBody[Z] + dZdot1 / 2.0, angRatesBody[PITCH] + dThetaDot1 / 2.0, angRatesBody[YAW] + dPsiDot1 / 2.0);
    dX2 = dt * (velBody[X] + dX1 / 2.0);
    dYdot2 = dt * udot(velBody[X] + dXdot1 / 2.0, velBody[Z] + dZdot1 / 2.0, angRatesBody[ROLL] + dPhiDot1 / 2.0, angRatesBody[YAW] + dPsiDot1 / 2.0);
    dY2 = dt * (velBody[Y] + dY1 / 2.0);
    dZdot2 = dt * udot(velBody[X] + dXdot1 / 2.0, velBody[Y] + dYdot1 / 2.0, angRatesBody[ROLL] + dPhiDot1 / 2.0, angRatesBody[PITCH] + dThetaDot1 / 2.0);
    dZ2 = dt * (velBody[Z] + dZ1 / 2.0);

    dEulerAngRates = angularRatesDerivative(angRatesBody[ROLL] + dPhiDot1 / 2.0, angRatesBody[PITCH] + dThetaDot1 / 2.0, angRatesBody[YAW] + dPsiDot1 / 2.0);

    dPhiDot2 = dt * dEulerAngRates[ROLL];
    dPhi2 = dt * (angRatesBody[ROLL] + dPhi1 / 2.0);
    dThetaDot2 = dt * dEulerAngRates[PITCH];
    dTheta2 = dt * (angRatesBody[PITCH] + dTheta1 / 2.0);
    dPsiDot2 = dt * dEulerAngRates[YAW];
    dPsi2 = dt * (angRatesBody[YAW] + dPsi1 / 2.0);


    // k3
    dXdot3 = dt * udot(velBody[Y] + dYdot2 / 2.0, velBody[Z] + dZdot2 / 2.0, angRatesBody[PITCH] + dThetaDot2 / 2.0, angRatesBody[YAW] + dPsiDot2 / 2.0);
    dX3 = dt * (velBody[X] + dX2 / 2.0);
    dYdot3 = dt * udot(velBody[X] + dXdot2 / 2.0, velBody[Z] + dZdot2 / 2.0, angRatesBody[ROLL] + dPhiDot2 / 2.0, angRatesBody[YAW] + dPsiDot2 / 2.0);
    dY3 = dt * (velBody[Y] + dY2 / 2.0);
    dZdot3 = dt * udot(velBody[X] + dXdot2 / 2.0, velBody[Y] + dYdot2 / 2.0, angRatesBody[ROLL] + dPhiDot2 / 2.0, angRatesBody[PITCH] + dThetaDot2 / 2.0);
    dZ3 = dt * (velBody[Z] + dZ2 / 2.0);

    dEulerAngRates = angularRatesDerivative(angRatesBody[ROLL] + dPhiDot2 / 2.0, angRatesBody[PITCH] + dThetaDot2 / 2.0, angRatesBody[YAW] + dPsiDot2 / 2.0);

    dPhiDot3 = dt * dEulerAngRates[ROLL];
    dPhi3 = dt * (angRatesBody[ROLL] + dPhi2 / 2.0);
    dThetaDot3 = dt * dEulerAngRates[PITCH];
    dTheta3 = dt * (angRatesBody[PITCH] + dTheta2 / 2.0);
    dPsiDot3 = dt * dEulerAngRates[YAW];
    dPsi3 = dt * (angRatesBody[YAW] + dPsi2 / 2.0);


    // k4
    dXdot4 = dt * udot(velBody[Y] + dYdot3, velBody[Z] + dZdot3, angRatesBody[PITCH] + dThetaDot3, angRatesBody[YAW] + dPsiDot3);
    dX4 = dt * (velBody[X] + dX3);
    dYdot4 = dt * udot(velBody[X] + dXdot3, velBody[Z] + dZdot3, angRatesBody[ROLL] + dPhiDot3, angRatesBody[YAW] + dPsiDot3);
    dY4 = dt * (velBody[Y] + dY3);
    dZdot4 = dt * udot(velBody[X] + dXdot3, velBody[Y] + dYdot3, angRatesBody[ROLL] + dPhiDot3, angRatesBody[PITCH] + dThetaDot3);
    dZ4 = dt * (velBody[Z] + dZ3);

    dEulerAngRates = angularRatesDerivative(angRatesBody[ROLL] + dPhiDot3, angRatesBody[PITCH] + dThetaDot3, angRatesBody[YAW] + dPsiDot3);

    dPhiDot4 = dt * dEulerAngRates[ROLL];
    dPhi4 = dt * (angRatesBody[ROLL] + dPhi3);
    dThetaDot4 = dt * dEulerAngRates[PITCH];
    dTheta4 = dt * (angRatesBody[PITCH] + dTheta3);
    dPsiDot4 = dt * dEulerAngRates[YAW];
    dPsi4 = dt * (angRatesBody[YAW] + dPsi3);


    // Update state
    velBody[X] += (dXdot1 + 2.0 * dXdot2 + 2.0 * dXdot3 + dXdot4) / 6.0;
    velBody[Y] += (dYdot1 + 2.0 * dYdot2 + 2.0 * dYdot3 + dYdot4) / 6.0;
    velBody[Z] += (dZdot1 + 2.0 * dZdot2 + 2.0 * dZdot3 + dZdot4) / 6.0;

    myMath::Vector3d dPosBody;
    dPosBody[X] = (dX1 + 2.0 * dX2 + 2.0 * dX3 + dX4) / 6.0;
    dPosBody[Y] = (dY1 + 2.0 * dY2 + 2.0 * dY3 + dY4) / 6.0;
    dPosBody[Z] = (dZ1 + 2.0 * dZ2 + 2.0 * dZ3 + dZ4) / 6.0;

    posEci += myMath::Transpose(bodyFromEci) * dPosBody;

    angRatesBody[ROLL] += (dPhiDot1 + 2.0 * dPhiDot2 + 2.0 * dPhiDot3 + dPhiDot4) / 6.0;
    angRatesBody[PITCH] += (dThetaDot1 + 2.0 * dThetaDot2 + 2.0 * dThetaDot3 + dThetaDot4) / 6.0;
    angRatesBody[YAW] += (dPsiDot1 + 2.0 * dPsiDot2 + 2.0 * dPsiDot3 + dPsiDot4) / 6.0;

    eulerAngles[ROLL] += (dPhi1 + 2.0 * dPhi2 + 2.0 * dPhi3 + dPhi4) / 6.0;
    eulerAngles[PITCH] += (dTheta1 + 2.0 * dTheta2 + 2.0 * dTheta3 + dTheta4) / 6.0;
    eulerAngles[YAW] += (dPsi1 + 2.0 * dPsi2 + 2.0 * dPsi3 + dPsi4) / 6.0;
}

void eom::finalize()
{
    // Do nothing
}

void eom::updateDCMs()
{
    earthRotation += myMath::Constants::EARTH_ROTATION_RATE * dt;
    ecefFromEci[0][0] = std::cos(earthRotation);
    ecefFromEci[0][1] = std::sin(earthRotation);
    ecefFromEci[0][2] = 0.0;

    ecefFromEci[1][0] = -std::sin(earthRotation);
    ecefFromEci[1][1] = std::cos(earthRotation);
    ecefFromEci[1][2] = 0.0;

    ecefFromEci[2][0] = 0.0;
    ecefFromEci[2][1] = 0.0;
    ecefFromEci[2][2] = 1.0;

    posEcef = ecefFromEci * posEci;

    lat_centric = std::asin(posEcef[2] / posEcef.Magnitude());
    lon_centric = std::atan2(posEcef[1], posEcef[0]);

    lon_detic = lon_centric;

    double eps = 1.0e-8;
    lat_detic = std::atan2(posEcef[Z], std::sqrt(myMath::SQ(posEcef[X]) + myMath::SQ(posEcef[Y])));
    double lastItr;

    for (unsigned int i{0u}; i < 30u && (std::abs(lat_detic - lastItr) > eps); i++)
    {
        lastItr = lat_detic;

        lat_detic = std::atan2(
                        posEcef[Z] + myMath::Constants::EARTH_POLAR_RADIUS * myMath::SQ(myMath::Constants::EARTH_ECCENTRICITY) * std::sin(lat_detic),
                        std::sqrt(myMath::SQ(posEcef[X]) + myMath::SQ(posEcef[Y]) - myMath::SQ(myMath::Constants::EARTH_ECCENTRICITY) * myMath::Constants::EARTH_EQUITORIAL_RADIUS * myMath::SQ(std::cos(lat_detic))));
    }

    if (std::abs(lat_detic - lastItr) > eps)
    {
        std::cout << "Warning: Detic latitude did not converge to within " << eps << " radians. Delta = " << std::abs(lat_detic - lastItr) << " radians." << std::endl;
    }

    enuFromEcef[0][0] = -std::sin(lon_detic);
    enuFromEcef[0][1] = std::cos(lon_detic);
    enuFromEcef[0][2] = 0.0;

    enuFromEcef[1][0] = -std::sin(lat_detic) * std::cos(lon_detic);
    enuFromEcef[1][1] = -std::sin(lat_detic) * std::sin(lon_detic);
    enuFromEcef[1][2] = std::cos(lat_detic);

    enuFromEcef[2][0] = std::cos(lat_detic) * std::cos(lon_detic);
    enuFromEcef[2][1] = std::cos(lat_detic) * std::sin(lon_detic);
    enuFromEcef[2][2] = std::sin(lat_detic);

    nedFromEcef = enuFromNed.Transpose() * enuFromEcef;

    myMath::Matrix3d R_roll;
    myMath::Matrix3d R_pitch;
    myMath::Matrix3d R_yaw;

    R_roll[0][0] = 1.0;
    R_roll[0][1] = 0.0;
    R_roll[0][2] = 0.0;

    R_roll[1][0] = 0.0;
    R_roll[1][1] = std::cos(eulerAngles[ROLL]);
    R_roll[1][2] = std::sin(eulerAngles[ROLL]);

    R_roll[2][0] = 0.0;
    R_roll[2][1] = -std::sin(eulerAngles[ROLL]);
    R_roll[2][2] = std::cos(eulerAngles[ROLL]);

    R_pitch[0][0] = std::cos(eulerAngles[PITCH]);
    R_pitch[0][1] = 0.0;
    R_pitch[0][2] = -std::sin(eulerAngles[PITCH]);

    R_pitch[1][0] = 0.0;
    R_pitch[1][1] = 1.0;
    R_pitch[1][2] = 0.0;

    R_pitch[2][0] = std::sin(eulerAngles[PITCH]);
    R_pitch[2][1] = 0.0;
    R_pitch[2][2] = std::cos(eulerAngles[PITCH]);

    R_yaw[0][0] = std::cos(eulerAngles[YAW]);
    R_yaw[0][1] = std::sin(eulerAngles[YAW]);
    R_yaw[0][2] = 0.0;

    R_yaw[1][0] = -std::sin(eulerAngles[YAW]);
    R_yaw[1][1] = std::cos(eulerAngles[YAW]);
    R_yaw[1][2] = 0.0;

    R_yaw[2][0] = 0.0;
    R_yaw[2][1] = 0.0;
    R_yaw[2][2] = 1.0;

    bodyFromNed = R_yaw * R_pitch * R_roll;

    bodyFromEcef = bodyFromNed * nedFromEcef;

    bodyFromEci = bodyFromEcef * ecefFromEci;

    velEcef = bodyFromEcef.Transpose() * velBody;
    windVelBody = -velBody + naturalWindVelBody;

    angleOfAttack = std::atan2(velBody[Z], velBody[X]) + Aircraft::WingIncidenceAngle;

    angleOfSideslip = std::asin(velBody[Y] / velBody.Magnitude());

    flightPathAngle = eulerAngles[PITCH] - angleOfAttack;

    angleOfAttackTotal = std::acos(velBody[X] / velBody.Magnitude());
    // angleOfAttackTotal = std::acos(std::cos(angleOfAttack) * std::cos(angleOfSideslip));

    angleOfAttackTotalClockAng = std::atan2(velBody[Y], velBody[Z]);

    bodyFromWind[0][0] = std::cos(angleOfAttack) * std::cos(angleOfSideslip);
    bodyFromWind[0][1] = std::sin(angleOfSideslip);
    bodyFromWind[0][2] = std::sin(angleOfAttack) * std::cos(angleOfSideslip);

    bodyFromWind[1][0] = -std::cos(angleOfAttack) * std::sin(angleOfSideslip);
    bodyFromWind[1][1] = std::cos(angleOfSideslip);
    bodyFromWind[1][2] = -std::sin(angleOfAttack) * std::sin(angleOfSideslip);

    bodyFromWind[2][0] = -std::sin(angleOfAttack);
    bodyFromWind[2][1] = 0.0;
    bodyFromWind[2][2] = std::cos(angleOfAttack);
}

double eom::udot(const double v, const double w, const double q, const double r)
{
    return (r * v - q * w) + (1.0 / mass) * (netForceBody[X]);
}

double eom::vdot(const double u, const double w, const double p, const double r)
{
    return (p * w - r * u) + (1.0 / mass) * (netForceBody[Y]);
}

double eom::wdot(const double u, const double v, const double p, const double q)
{
    return (q * u - p * v) + (1.0 / mass) * (netForceBody[Z]);
}

myMath::Vector3d eom::angularRatesDerivative(const double p, const double q, const double r)
{
    myMath::Vector3d angularRatesDerivs;

    angularRatesDerivs[ROLL] = -q * (-p * I[X][Z] - q * I[Y][Z] + r * I[Z][Z]) + r * (-p * I[X][Y] + q * I[Y][Y] - r * I[Y][Z]) + netMomentBody[ROLL];
    angularRatesDerivs[PITCH] = p * (-p * I[X][Z] - q * I[Y][Z] + r * I[Z][Z]) - r * (p * I[X][X] - q * I[X][Y] + r * I[X][Z]) + netMomentBody[PITCH];
    angularRatesDerivs[YAW] = -p * (-p * I[X][Y] + q * I[Y][Y] - r * I[Y][Z]) + q * (p * I[X][X] - q * I[X][Y] + r * I[X][Z]) + netMomentBody[YAW];

    return I.Inverse() * angularRatesDerivs;
}

void eom::addForces(const myMath::Vector3d &force)
{
    netForceBody += force;
}

void eom::addMoments(const myMath::Vector3d &moment)
{
    netMomentBody += moment;
}