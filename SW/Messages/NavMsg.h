#ifndef B25DAB41_D1E7_4D25_9D19_0F2F59867A12
#define B25DAB41_D1E7_4D25_9D19_0F2F59867A12

#include "MessagePayloadTemplate.hxx"

#include "MsgIds.hpp"

struct NavData
{
    float time;

    float posEci_raw[3];
    float velEci_raw[3];
    float accEci_raw[3];

    float posEcef_raw[3];
    float velEcef_raw[3];
    float accEcef_raw[3];

    float eulerAngs_raw[3];
    float eulerAngRates_raw[3];

    float bodyFromEcef_raw[3][3];
    float bodyFromNed_raw[3][3];

    float angleOfAttack;
    float angleOfSideslip;

    float angleOfAttackDot;
    float angleOfSideslipDot;

    float altSeaLevel;

    float gravityEcef_raw[3];

    float mach;

    void Default()
    {
        time = 0.0f;

        angleOfAttack   = 0.0f;
        angleOfSideslip = 0.0f;

        angleOfAttackDot   = 0.0f;
        angleOfSideslipDot = 0.0f;

        altSeaLevel = 0.0f;

        mach = 0.0f;

        for ( unsigned int i{0u}; i < 3u; i++ )
        {
            posEci_raw[i] = 0.0f;
            velEci_raw[i] = 0.0f;
            accEci_raw[i] = 0.0f;

            posEcef_raw[i] = 0.0f;
            velEcef_raw[i] = 0.0f;
            accEcef_raw[i] = 0.0f;

            eulerAngs_raw[i]     = 0.0f;
            eulerAngRates_raw[i] = 0.0f;

            gravityEcef_raw[i] = 0.0f;

            for ( unsigned int j{0u}; i < 3u; i++ )
            {
                bodyFromEcef_raw[i][j] = 0.0f;
                bodyFromNed_raw[i][j]  = 0.0f;
            }
        }
    }

    NavData()
        : time()
        , posEci_raw()
        , velEci_raw()
        , accEci_raw()
        , posEcef_raw()
        , velEcef_raw()
        , accEcef_raw()
        , eulerAngs_raw()
        , eulerAngRates_raw()
        , bodyFromEcef_raw()
        , bodyFromNed_raw()
        , angleOfAttack()
        , angleOfSideslip()
        , angleOfAttackDot()
        , angleOfSideslipDot()
        , altSeaLevel()
        , gravityEcef_raw()
        , mach()
    {
        Default();
    }
};

MESSAGE_PAYLOAD( NavMsg, NavData, NavMsgId )

#endif /* B25DAB41_D1E7_4D25_9D19_0F2F59867A12 */
