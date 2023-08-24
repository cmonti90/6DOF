#ifndef B257F02C_D0B4_4681_96FB_95A1AA9E9CC6
#define B257F02C_D0B4_4681_96FB_95A1AA9E9CC6

#include "Vector.h"
#include "Constants.h"

#include <cmath>

namespace WGS84
{
    void ecefToLla(const myMath::Vector3d& posEcef, double &lat, double &lon, double &alt)
    {
        // WGS84 constants
        const double e2 = 1.0 - myMath::SQ(myMath::Constants::EARTH_POLAR_RADIUS) / myMath::SQ(myMath::Constants::EARTH_EQUITORIAL_RADIUS);  // first eccentricity squared
        const double ep2 = myMath::SQ(myMath::Constants::EARTH_EQUITORIAL_RADIUS) / myMath::SQ(myMath::Constants::EARTH_POLAR_RADIUS) - 1.0; // second eccentricity squared

        // calculations
        const double p = std::sqrt(myMath::SQ(posEcef[0]) + myMath::SQ(posEcef[1]));
        const double theta = std::atan2((posEcef[2] * myMath::Constants::EARTH_EQUITORIAL_RADIUS), (p * myMath::Constants::EARTH_POLAR_RADIUS));
        lat = std::atan2(posEcef[2] + ep2 * myMath::Constants::EARTH_POLAR_RADIUS * std::pow(std::sin(theta), 3), p - e2 * myMath::Constants::EARTH_EQUITORIAL_RADIUS * std::pow(std::cos(theta) , 3));
        lon = std::atan2(posEcef[1], posEcef[0]);

        const double v = myMath::Constants::EARTH_EQUITORIAL_RADIUS / std::sqrt(1.0 - e2 * std::sin(lat) * std::sin(lat));
        alt = (p / std::cos(lat)) - v;
    }

    void llaToEcef(const double lat, const double lon, const double alt, myMath::Vector3d &posEcef)
    {
        // WGS84 constants
        const double e2 = 1.0 - myMath::SQ(myMath::Constants::EARTH_POLAR_RADIUS) / myMath::SQ(myMath::Constants::EARTH_EQUITORIAL_RADIUS);  // first eccentricity squared
        const double ep2 = myMath::SQ(myMath::Constants::EARTH_EQUITORIAL_RADIUS) / myMath::SQ(myMath::Constants::EARTH_POLAR_RADIUS) - 1.0; // second eccentricity squared

        // calculations
        const double N = myMath::Constants::EARTH_EQUITORIAL_RADIUS / std::sqrt(1.0 - e2 * std::sin(lat) * std::sin(lat));
        posEcef[0] = (N + alt) * std::cos(lat) * std::cos(lon);
        posEcef[1] = (N + alt) * std::cos(lat) * std::sin(lon);
        posEcef[2] = (N * (1.0 - e2) + alt) * std::sin(lat);
    }

} // namespace WGS84

#endif /* B257F02C_D0B4_4681_96FB_95A1AA9E9CC6 */
