#ifndef B25DAB41_D1E7_4D25_9D19_0F2F59867A12
#define B25DAB41_D1E7_4D25_9D19_0F2F59867A12

#include "MessagePayloadTemplate.hxx"

#include "MsgIds.hpp"

struct NavData
{
    double posEci_raw[3];
    double velEci_raw[3];
    double accEci_raw[3];

    double posEcef_raw[3];
    double velEcef_raw[3];
    double accEcef_raw[3];

    double eulerAngs_raw[3];
    double eulerAngRates_raw[3];

    double bodyFromNed_raw[3][3];

    double angleOfAttack;
    double angleOfSideslip;

    double angleOfAttackDot;
    double angleOfSideslipDot;

    double altSeaLevel;

    void Default()
    {
        angleOfAttack = 0.0;
        angleOfSideslip = 0.0;

        angleOfAttackDot = 0.0;
        angleOfSideslipDot = 0.0;

        altSeaLevel = 0.0;

        for (unsigned int i{0u}; i < 3u; i++)
        {
            posEci_raw[i] = 0.0;
            velEci_raw[i] = 0.0;
            accEci_raw[i] = 0.0;

            posEcef_raw[i] = 0.0;
            velEcef_raw[i] = 0.0;
            accEcef_raw[i] = 0.0;

            eulerAngs_raw[i] = 0.0;
            eulerAngRates_raw[i] = 0.0;
        }
    }

    NavData() : posEci_raw(),
                velEci_raw(),
                accEci_raw(),
                posEcef_raw(),
                velEcef_raw(),
                accEcef_raw(),
                eulerAngs_raw(),
                eulerAngRates_raw(),
                angleOfAttack(),
                angleOfSideslip(),
                angleOfAttackDot(),
                angleOfSideslipDot(),
                altSeaLevel()
    {
        Default();
    }
};

MESSAGE_PAYLOAD(NavMsg, NavData, NavMsgId)

#endif /* B25DAB41_D1E7_4D25_9D19_0F2F59867A12 */
