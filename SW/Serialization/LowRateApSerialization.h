#ifndef LOW_RATE_AP_SERIALIZATION_H
#define LOW_RATE_AP_SERIALIZATION_H

#include "LowRateAutopilotMsg.h"

#include "Decorators.h"
#include "myMathVector.h"


struct APGains
{
    APGains()
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
    {}

    virtual ~APGains() {};

    void Reset()
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

    float maxAlpha; // Maximum angle of attack for the missile  [rad]

    float Kp;       // Roll Rate Gain                           [s]
    float Kq;       // Pitch Rate Gain                          [s]
    float Kr;       // Yaw Rate Gain                            [s]

    float KPhi;     // Roll Angle Gain                          [-]
    float KTheta;   // Pitch Angle Gain                         [-]
    float KPsi;     // Yaw Angle Gain                           [-]

    float KAr;      // Roll Angle Error Gain                    [1/s]
    float KAz;      // Pitch Angle Error Gain                   [rad/s/G]
    float KAy;      // Yaw Angle Error Gain                     [rad/s/G]

    float KAlpha;  // State Decoupling Gain                      [-]
    float KBeta;   // State Decoupling Gain                      [-]

    float KRR;     // Element of Control Decoupling Gain Matrix  [-]
    float KRP;     // Element of Control Decoupling Gain Matrix  [-]
    float KRY;     // Element of Control Decoupling Gain Matrix  [-]

    float KPR;     // Element of Control Decoupling Gain Matrix  [-]
    float KPP;     // Element of Control Decoupling Gain Matrix  [-]
    float KPY;     // Element of Control Decoupling Gain Matrix  [-]

    float KYR;     // Element of Control Decoupling Gain Matrix  [-]
    float KYP;     // Element of Control Decoupling Gain Matrix  [-]
    float KYY;     // Element of Control Decoupling Gain Matrix  [-]

    float Kffr;    // Fin Feedback Roll Gain                     [-]
    float Kffp;    // Fin Feedback Pitch Gain                    [-]
    float Kffy;    // Fin Feedback Yaw Gain                      [-]

    float IKRR;    // Element of Inverse of Control Decoupling Gain Matrix  [-]
    float IKRP;    // Element of Inverse of Control Decoupling Gain Matrix  [-]
    float IKRY;    // Element of Inverse of Control Decoupling Gain Matrix  [-]

    float IKPR;    // Element of Inverse of Control Decoupling Gain Matrix  [-]
    float IKPP;    // Element of Inverse of Control Decoupling Gain Matrix  [-]
    float IKPY;    // Element of Inverse of Control Decoupling Gain Matrix  [-]

    float IKYR;    // Element of Inverse of Control Decoupling Gain Matrix  [-]
    float IKYP;    // Element of Inverse of Control Decoupling Gain Matrix  [-]
    float IKYY;    // Element of Inverse of Control Decoupling Gain Matrix  [-]

    float KssQ0;   // Steady-State Pitch Rate Command Gain                  [rad/s]
    float KssR0;   // Steady-State Yaw Rate Command Gain                    [rad/s]

};

struct LowRateApDeserializedData
{
    APGains apGains;

    LowRateApDeserializedData()
        : apGains()
    {
    }

    virtual void initialize()
    {
        apGains.Reset();
    }

    virtual void reset()
    {
        initialize();
    }
};

template <>
struct PayloadSerializer< LowRateAutopilotData > : LowRateApDeserializedData
{
    PayloadSerializer()
    : LowRateApDeserializedData()
    {
    }

    void serialize( LowRateAutopilotData& payload ) const
    {
        payload.Kp       = apGains.Kp;
        payload.Kq       = apGains.Kq;
        payload.Kr       = apGains.Kr;

        payload.KPhi     = apGains.KPhi;
        payload.KTheta   = apGains.KTheta;
        payload.KPsi     = apGains.KPsi;

        payload.KAr      = apGains.KAr;
        payload.KAz      = apGains.KAz;
        payload.KAy      = apGains.KAy;

        payload.KAlpha   = apGains.KAlpha;
        payload.KBeta    = apGains.KBeta;

        payload.KRR      = apGains.KRR;
        payload.KRP      = apGains.KRP;
        payload.KRY      = apGains.KRY;

        payload.KPR      = apGains.KPR;
        payload.KPP      = apGains.KPP;
        payload.KPY      = apGains.KPY;

        payload.KYR      = apGains.KYR;
        payload.KYP      = apGains.KYP;
        payload.KYY      = apGains.KYY;

        payload.Kffr     = apGains.Kffr;
        payload.Kffp     = apGains.Kffp;
        payload.Kffy     = apGains.Kffy;

        payload.IKRR     = apGains.IKRR;
        payload.IKRP     = apGains.IKRP;
        payload.IKRY     = apGains.IKRY;

        payload.IKPR     = apGains.IKPR;
        payload.IKPP     = apGains.IKPP;
        payload.IKPY     = apGains.IKPY;

        payload.IKYR     = apGains.IKYR;
        payload.IKYP     = apGains.IKYP;
        payload.IKYY     = apGains.IKYY;

        payload.KssQ0    = apGains.KssQ0;
        payload.KssR0    = apGains.KssR0;
    }
};

template <>
struct PayloadDeserializer< LowRateAutopilotData > : LowRateApDeserializedData
{
    PayloadDeserializer()
    : LowRateApDeserializedData()
    {
    }

    void deserialize( const LowRateAutopilotData& payload )
    {
        apGains.Kp       = payload.Kp;
        apGains.Kq       = payload.Kq;
        apGains.Kr       = payload.Kr;

        apGains.KPhi     = payload.KPhi;
        apGains.KTheta   = payload.KTheta;
        apGains.KPsi     = payload.KPsi;

        apGains.KAr      = payload.KAr;
        apGains.KAz      = payload.KAz;
        apGains.KAy      = payload.KAy;

        apGains.KAlpha   = payload.KAlpha;
        apGains.KBeta    = payload.KBeta;

        apGains.KRR      = payload.KRR;
        apGains.KRP      = payload.KRP;
        apGains.KRY      = payload.KRY;

        apGains.KPR      = payload.KPR;
        apGains.KPP      = payload.KPP;
        apGains.KPY      = payload.KPY;

        apGains.KYR      = payload.KYR;
        apGains.KYP      = payload.KYP;
        apGains.KYY      = payload.KYY;

        apGains.Kffr     = payload.Kffr;
        apGains.Kffp     = payload.Kffp;
        apGains.Kffy     = payload.Kffy;

        apGains.IKRR     = payload.IKRR;
        apGains.IKRP     = payload.IKRP;
        apGains.IKRY     = payload.IKRY;

        apGains.IKPR     = payload.IKPR;
        apGains.IKPP     = payload.IKPP;
        apGains.IKPY     = payload.IKPY;

        apGains.IKYR     = payload.IKYR;
        apGains.IKYP     = payload.IKYP;
        apGains.IKYY     = payload.IKYY;

        apGains.KssQ0    = payload.KssQ0;
        apGains.KssR0    = payload.KssR0;
    }
};

#endif // LOW_RATE_AP_SERIALIZATION_H
