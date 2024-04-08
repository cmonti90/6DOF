#ifndef B257F02C_D0B4_4681_96FB_95A1AA9E9CC6
#define B257F02C_D0B4_4681_96FB_95A1AA9E9CC6

#include "myMathVector.h"

namespace WGS84
{
    void EcefToLla(const myMath::Vector3d& posEcef, double &lat, double &lon, double &alt);
    void LlaToEcef(const double lat, const double lon, const double alt, myMath::Vector3d &posEcef);

} // namespace WGS84

#endif /* B257F02C_D0B4_4681_96FB_95A1AA9E9CC6 */
