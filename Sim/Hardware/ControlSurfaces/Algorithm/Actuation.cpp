
#include "Actuation.h"

Actuation::Actuation()
    : Iaxis             ( 0.0 )
    , dampingCoeff      ( 0.0 )
    , angDeflStates     ( 0.0 )
    , stateErr          ( 0.0 )
    , stateErr_prev     ( 0.0 )
    , pid               ()
    , integrativeError  ( 0.0 )
{
}

Actuation::Actuation( const myMath::Vector3d& initAngDeflStates, const double inert, const double damping )
    : Iaxis             ( inert )
    , dampingCoeff      ( damping )
    , angDeflStates     ( initAngDeflStates )
    , stateErr          ( 0.0 )
    , stateErr_prev     ( 0.0 )
    , pid               ()
    , integrativeError  ( 0.0 )
{
}

Actuation::~Actuation()
{
}

void Actuation::initialize()
{
}

void Actuation::update( double cmd )
{
    stateErr_prev = stateErr;
    stateErr = cmd - angDeflStates[0];

    double PIDcmd = controller();

    stateDynamics( PIDcmd );
}

void Actuation::finalize()
{
}

void Actuation::setPID( double p, double i, double d )
{
    pid.p = p;
    pid.i = i;
    pid.d = d;
}

void Actuation::setIaxis( double inert )
{
    Iaxis = inert;
}

void Actuation::setDampingCoeff( double damping )
{
    dampingCoeff = damping;
}

double Actuation::getDeflection() const
{
    return angDeflStates[0];
}

double Actuation::controller()
{
    double PIDcmd = 0.0;
    double dt = 0.001;

    // Propotional
    PIDcmd += pid.p * stateErr;

    // Integral
    integrativeError += dt * stateErr;
    PIDcmd += pid.i * integrativeError;

    // Derivative
    // PIDcmd += pid.d * ( stateErr - stateErr_prev ) / dt;


    return PIDcmd;
}

void Actuation::stateDynamics( double cmd )
{
    double dt = 0.001;

    angDeflStates[2] = ( cmd - dampingCoeff * angDeflStates[1] ) / Iaxis;
    angDeflStates[1] += dt * angDeflStates[2];
    angDeflStates[0] += dt * angDeflStates[1];

    angDeflStates[0] = myMath::wrapMinusPiToPi( angDeflStates[0] );
}
