#ifndef DABE8334_1F6B_471B_BBDB_38B35BA70571
#define DABE8334_1F6B_471B_BBDB_38B35BA70571

#include "MessagePayloadTemplate.hxx"

#include "MsgIds.hpp"

#include "mathlib.h"

struct EomData
{
    myMath::Vector3d windVelBody;
    myMath::Vector3d velBody;
    myMath::Vector3d accelBody;

    myMath::Vector3d posEci;
    myMath::Vector3d velEci;

    myMath::Vector3d posEcef;
    myMath::Vector3d velEcef;

    myMath::Vector3d eulerAngs;
    myMath::Vector3d eulerAngRates;

    double angleOfAttack;
    double angleOfSideslip;

    double angleOfAttackDot;
    double angleOfSideslipDot;

    double altSeaLevel;

    myMath::Matrix3d bodyFromNed;
    myMath::Matrix3d bodyFromWind;

    void Default()
    {
        windVelBody = 0.0;
        velBody = 0.0;
        accelBody = 0.0;

        posEci = 0.0;
        velEci = 0.0;

        posEcef = 0.0;
        velEcef = 0.0;

        eulerAngs = 0.0;
        eulerAngRates = 0.0;

        angleOfAttack = 0.0;
        angleOfSideslip = 0.0;

        angleOfAttackDot = 0.0;
        angleOfSideslipDot = 0.0;

        altSeaLevel = 0.0;

        bodyFromNed = 0.0;
        bodyFromWind = 0.0;
    }

    EomData &operator=(const EomData &other)
    {
        windVelBody = other.windVelBody;
        velBody = other.velBody;
        accelBody = other.accelBody;

        posEci = other.posEci;
        velEci = other.velEci;

        posEcef = other.posEcef;
        velEcef = other.velEcef;

        eulerAngs = other.eulerAngs;
        eulerAngRates = other.eulerAngRates;

        angleOfAttack = other.angleOfAttack;
        angleOfSideslip = other.angleOfSideslip;

        angleOfAttackDot = other.angleOfAttackDot;
        angleOfSideslipDot = other.angleOfSideslipDot;

        altSeaLevel = other.altSeaLevel;

        bodyFromNed = other.bodyFromNed;
        bodyFromWind = other.bodyFromWind;

        return *this;
    }

    EomData()
        : windVelBody(),
          velBody(),
          accelBody(),
          posEci(),
          velEci(),
          posEcef(),
          velEcef(),
          eulerAngs(),
          eulerAngRates(),
          angleOfAttack(),
          angleOfSideslip(),
          angleOfAttackDot(),
          angleOfSideslipDot(),
          altSeaLevel(),
          bodyFromNed(),
          bodyFromWind()
    {
        Default();
    }

    EomData(const EomData &other)
        : windVelBody(other.windVelBody),
          velBody(other.velBody),
          accelBody(other.accelBody),
          posEci(other.posEci),
          velEci(other.velEci),
          posEcef(other.posEcef),
          velEcef(other.velEcef),
          eulerAngs(other.eulerAngs),
          eulerAngRates(other.eulerAngRates),
          angleOfAttack(other.angleOfAttack),
          angleOfSideslip(other.angleOfSideslip),
          angleOfAttackDot(other.angleOfAttackDot),
          angleOfSideslipDot(other.angleOfSideslipDot),
          altSeaLevel(other.altSeaLevel),
          bodyFromNed(other.bodyFromNed),
          bodyFromWind(other.bodyFromWind)
    {
    }
};

MESSAGE_PAYLOAD(EomMsg, EomData, EomMsgId)

#endif /* DABE8334_1F6B_471B_BBDB_38B35BA70571 */
