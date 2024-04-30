#ifndef LOWRATEAUTOPILOTMSG_H
#define LOWRATEAUTOPILOTMSG_H

#include "MessagePayloadTemplate.hxx"

#include "MsgIds.hpp"


struct LowRateAutopilotData
{
    float maxG;
    float accelCmdRateLimit;
    float cmdErrorLimit;
    float rollCmdErrorLimit;
    float finStallLimit;

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

    float rollLowPassFilterNum[3];
    float rollLowPassFilterDen[2];
    float rollNotchFilterNum[3];
    float rollNotchFilterDen[2];
    float rollCompFilterNum[3];
    float rollCompFilterDen[2];

    float lateralLowPassFilterNum[3];
    float lateralLowPassFilterDen[2];
    float lateralNotchFilter1Num[3];
    float lateralNotchFilter1Den[2];
    float lateralNotchFilter2Num[3];
    float lateralNotchFilter2Den[2];
    float lateralCompFilterNum[3];
    float lateralCompFilterDen[2];

    void Default()
    {
        maxG = 0.0f;
        accelCmdRateLimit = 0.0f;
        cmdErrorLimit = 0.0f;
        rollCmdErrorLimit = 0.0f;
        finStallLimit = 0.0f;

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

        for ( int i = 0; i < 3; i++ )
        {
            rollLowPassFilterNum[i] = 0.0f;
            rollNotchFilterNum[i] = 0.0f;
            rollCompFilterNum[i] = 0.0f;

            lateralLowPassFilterNum[i] = 0.0f;
            lateralNotchFilter1Num[i] = 0.0f;
            lateralNotchFilter2Num[i] = 0.0f;
            lateralCompFilterNum[i] = 0.0f;
        }

        for ( int i = 0; i < 2; i++ )
        {
            rollLowPassFilterDen[i] = 0.0f;
            rollNotchFilterDen[i] = 0.0f;
            rollCompFilterDen[i] = 0.0f;

            lateralLowPassFilterDen[i] = 0.0f;
            lateralNotchFilter1Den[i] = 0.0f;
            lateralNotchFilter2Den[i] = 0.0f;
            lateralCompFilterDen[i] = 0.0f;
        }
    }

    LowRateAutopilotData()
    {
        Default();
    }
};

MESSAGE_PAYLOAD( LowRateAutopilotMsg, LowRateAutopilotData, LowRateApMsgId )


#endif // LOWRATEAUTOPILOTMSG_H
