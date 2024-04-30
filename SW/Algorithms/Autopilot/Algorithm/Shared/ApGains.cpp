
#include "ApGains.h"

APGains::APGains()
: maxAlpha( 0.0f )

, Kp( 0.0f )
, Kq( 0.0f )
, Kr( 0.0f )

, KPhi( 0.0f )
, KTheta( 0.0f )
, KPsi( 0.0f )

, KAr( 0.0f )
, KAz( 0.0f )
, KAy( 0.0f )

, KAlpha( 0.0f )
, KBeta( 0.0f )

, KRR( 0.0f )
, KRP( 0.0f )
, KRY( 0.0f )

, KPR( 0.0f )
, KPP( 0.0f )
, KPY( 0.0f )

, KYR( 0.0f )
, KYP( 0.0f )
, KYY( 0.0f )

, Kffr( 0.0f )
, Kffp( 0.0f )
, Kffy( 0.0f )

, IKRR( 0.0f )
, IKRP( 0.0f )
, IKRY( 0.0f )

, IKPR( 0.0f )
, IKPP( 0.0f )
, IKPY( 0.0f )

, IKYR( 0.0f )
, IKYP( 0.0f )
, IKYY( 0.0f )

, KssQ0( 0.0f )
, KssR0( 0.0f )
{
}

APGains::~APGains()
{
}

void APGains::Reset()
{
    maxAlpha = 0.0f;

    Kp = 0.0f;
    Kq = 0.0f;
    Kr = 0.0f;

    KPhi   = 0.0f;
    KTheta = 0.0f;
    KPsi   = 0.0f;

    KAr = 0.0f;
    KAz = 0.0f;
    KAy = 0.0f;

    KAlpha = 0.0f;
    KBeta  = 0.0f;

    KRR = 0.0f;
    KRP = 0.0f;
    KRY = 0.0f;

    KPR = 0.0f;
    KPP = 0.0f;
    KPY = 0.0f;

    KYR = 0.0f;
    KYP = 0.0f;
    KYY = 0.0f;

    Kffr = 0.0f;
    Kffp = 0.0f;
    Kffy = 0.0f;

    IKRR = 0.0f;
    IKRP = 0.0f;
    IKRY = 0.0f;

    IKPR = 0.0f;
    IKPP = 0.0f;
    IKPY = 0.0f;

    IKYR = 0.0f;
    IKYP = 0.0f;
    IKYY = 0.0f;

    KssQ0 = 0.0f;
    KssR0 = 0.0f;
}