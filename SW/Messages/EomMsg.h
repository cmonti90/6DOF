#ifndef DABE8334_1F6B_471B_BBDB_38B35BA70571
#define DABE8334_1F6B_471B_BBDB_38B35BA70571

#include "MessagePayloadTemplate.hxx"

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
          angleOfSideslip()
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
          angleOfSideslip(other.angleOfSideslip)
    {
    }
};

MESSAGE_PAYLOAD(EomMsg, EomData, 50)

#endif /* DABE8334_1F6B_471B_BBDB_38B35BA70571 */
