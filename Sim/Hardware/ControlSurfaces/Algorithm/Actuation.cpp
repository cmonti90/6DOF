
#include "Actuation.h"

Actuation::Actuation()
    : Iaxis             ( 0.0 )
    , dampingCoeff      ( 0.0 )
    , angDeflStates     ( 0.0 )
    , stateErr          ( 0.0 )
    , stateErr_prev     ( 0.0 )
    , stateErr_prev2    ( 0.0 )
    , pid               ()
    , integrativeError  ( 0.0 )
    , PIDcmd            ( 0.0 )
    , PIDcmd_prev       ( 0.0 )
    , PIDcmd_prev2      ( 0.0 )
{
}

Actuation::Actuation( const myMath::Vector3d& initAngDeflStates, const double inert, const double damping )
    : Iaxis             ( inert )
    , dampingCoeff      ( damping )
    , angDeflStates     ( initAngDeflStates )
    , stateErr          ( 0.0 )
    , stateErr_prev     ( 0.0 )
    , stateErr_prev2    ( 0.0 )
    , pid               ()
    , integrativeError  ( 0.0 )
    , PIDcmd            ( 0.0 )
    , PIDcmd_prev       ( 0.0 )
    , PIDcmd_prev2      ( 0.0 )
{
}

Actuation::~Actuation()
{
}

void Actuation::initialize()
{
}

void Actuation::update( const double cmd )
{
    stateErr_prev2 = stateErr_prev;
    stateErr_prev = stateErr;
    stateErr = cmd - angDeflStates[0];

    PIDcmd_prev2 = PIDcmd_prev;
    PIDcmd_prev = PIDcmd;

    Controller();
    RungeKutta4thOrder( PIDcmd );
}

void Actuation::finalize()
{
}

void Actuation::setPID( const double p, const double i, const double d, double filterCoef )
{
    pid.p = p;
    pid.i = i;
    pid.d = d;
    pid.filterCoef = filterCoef;
}

void Actuation::setIaxis( const double inert )
{
    Iaxis = inert;
}

void Actuation::setDampingCoeff( const double damping )
{
    dampingCoeff = damping;
}

double Actuation::getDeflection() const
{
    return angDeflStates[0];
}

double Actuation::getControllerCmd() const
{
    return PIDcmd;
}

void Actuation::Controller()
{
    double newCmd = 0.0;
    const double dt = 0.001;

    // Propotional
    newCmd += pid.p * ( ( 1.0 + pid.filterCoef * dt ) * stateErr - ( 2.0 + pid.filterCoef * dt ) * stateErr_prev + stateErr_prev2 );

    // Integral
    newCmd += pid.i * dt * ( ( 1.0 + pid.filterCoef * dt ) * stateErr - stateErr_prev );

    // Derivative
    newCmd += pid.d * pid.filterCoef * ( stateErr - 2.0 * stateErr_prev + stateErr_prev2 );

    // Command
    PIDcmd = ( newCmd + ( 2.0 + pid.filterCoef * dt ) * PIDcmd_prev - PIDcmd_prev2 ) / ( 1.0 + pid.filterCoef * dt );

}

double Actuation::stateDynamics( const double cmd, const double thetaDot )
{
    return (( cmd - dampingCoeff * thetaDot ) / Iaxis);
}

void Actuation::RungeKutta4thOrder( const double cmd )
{
    const double dt = 0.001;

    double dThetaDot[4];
    double dTheta[4];

    angDeflStates[2] = stateDynamics( cmd, angDeflStates[1] );

    dThetaDot[0]    = dt * angDeflStates[2];
    dTheta[0]       = dt * angDeflStates[1];

    dThetaDot[1]    = dt * stateDynamics( cmd, angDeflStates[1] + 0.5 * dThetaDot[0] );
    dTheta[1]       = dt * ( angDeflStates[1] + dThetaDot[0] / 2.0 );

    dThetaDot[2]    = dt * stateDynamics( cmd, angDeflStates[1] + 0.5 * dThetaDot[1] );
    dTheta[2]       = dt * ( angDeflStates[1] + dThetaDot[1] / 2.0 );

    dThetaDot[3]    = dt * stateDynamics( cmd, angDeflStates[1] + dThetaDot[2] );
    dTheta[3]       = dt * ( angDeflStates[1] + dThetaDot[2] );

    angDeflStates[1] += ( dThetaDot[0] + 2.0 * dThetaDot[1] + 2.0 * dThetaDot[2] + dThetaDot[3] ) / 6.0;
    angDeflStates[0] += ( dTheta[0] + 2.0 * dTheta[1] + 2.0 * dTheta[2] + dTheta[3] ) / 6.0;

    angDeflStates[0] = myMath::wrapMinusPiToPi( angDeflStates[0] );

}