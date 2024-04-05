#ifndef APGAINS_H
#define APGAINS_H

struct APGains
{
    float maxAlpha; // Maximum angle of attack for the missile  [rad]

    float Kp;       // Roll Rate Gain                           [s]
    float Kq;       // Pitch Rate Gain                          [s]
    float Kr;       // Yaw Rate Gain                            [s]

    float Kphi;     // Roll Angle Gain                          [-]
    float Ktheta;   // Pitch Angle Gain                         [-]
    float Kpsi;     // Yaw Angle Gain                           [-]

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


#endif // APGAINS_H