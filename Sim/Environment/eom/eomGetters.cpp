

#include "eom.h"


double eom::getAltitudeSeaLevel() const
{
    return altSeaLevel_;
}

myMath::Vector3d eom::getPosEcef() const
{
    return posEcef_;
}

myMath::Vector3d eom::getVelEcef() const
{
    return velEcef_;
}

myMath::Vector3d eom::getAccelEcef() const
{
    return accelEcef_;
}

myMath::Vector3d eom::getAngRatesBody() const
{
    return angRatesBody_;
}