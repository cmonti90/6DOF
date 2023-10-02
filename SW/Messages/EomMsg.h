#ifndef DABE8334_1F6B_471B_BBDB_38B35BA70571
#define DABE8334_1F6B_471B_BBDB_38B35BA70571

#include "MessagePayloadTemplate.hxx"

#include "MsgIds.hpp"

#include "mathlib.h"

struct EomData
{
    double windVelBody_raw[3];
    double velBody_raw[3];
    double accelBody_raw[3];

    double posEci_raw[3];
    double velEci_raw[3];

    double posEcef_raw[3];
    double velEcef_raw[3];

    double eulerAngs_raw[3];
    double eulerAngRates_raw[3];

    double angleOfAttack;
    double angleOfSideslip;

    double angleOfAttackDot;
    double angleOfSideslipDot;

    double altSeaLevel;
    double altGeodetic;

    double lat;
    double lon;

    double bodyFromNed_raw[3][3];
    double bodyFromWind_raw[3][3];

    void Default()
    {
        angleOfAttack = 0.0;
        angleOfSideslip = 0.0;

        angleOfAttackDot = 0.0;
        angleOfSideslipDot = 0.0;

        altSeaLevel = 0.0;
        altGeodetic = 0.0;

        lat = 0.0;
        lon = 0.0;

        for (unsigned int i{0u}; i < 3u; i++)
        {
            windVelBody_raw[i] = 0.0;
            velBody_raw[i] = 0.0;
            accelBody_raw[i] = 0.0;

            posEci_raw[i] = 0.0;
            velEci_raw[i] = 0.0;

            posEcef_raw[i] = 0.0;
            velEcef_raw[i] = 0.0;

            eulerAngs_raw[i] = 0.0;
            eulerAngRates_raw[i] = 0.0;

            for (unsigned int j{0u}; j < 3u; j++)
            {
                bodyFromNed_raw[i][j] = 0.0;
                bodyFromWind_raw[i][j] = 0.0;
            }
        }
    }

    EomData()
        : windVelBody_raw(),
          velBody_raw(),
          accelBody_raw(),
          posEci_raw(),
          velEci_raw(),
          posEcef_raw(),
          velEcef_raw(),
          eulerAngs_raw(),
          eulerAngRates_raw(),
          angleOfAttack(),
          angleOfSideslip(),
          angleOfAttackDot(),
          angleOfSideslipDot(),
          altSeaLevel(),
          altGeodetic(),
          lat(),
          lon(),
          bodyFromNed_raw(),
          bodyFromWind_raw()
    {
        Default();
    }
};

MESSAGE_PAYLOAD(EomMsg, EomData, EomMsgId)

#endif /* DABE8334_1F6B_471B_BBDB_38B35BA70571 */
