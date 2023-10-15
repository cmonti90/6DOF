#include "WGS84.h"
#include "Constants.h"

#include <cmath>

namespace WGS84
{
    void EcefToLla( const myMath::Vector3d& posEcef, double& lat, double& lon, double& alt )
    {
        // WGS84 constants
        const double ecc2 = myMath::SQ( 8.1819190842622e-2 ); // first eccentricity
        const double b = myMath::Constants::EARTH_EQUITORIAL_RADIUS * std::sqrt( ( 1.0 - ecc2 ) );
        const double ep2 = myMath::SQ( myMath::Constants::EARTH_EQUITORIAL_RADIUS / b ) - 1.0; // second eccentricity squared

        // calculations
        const double p = std::sqrt( myMath::SQ( posEcef[0] ) + myMath::SQ( posEcef[1] ) );

        if ( myMath::isZero( p ) )
        {
            lat = posEcef[2] > 0.0 ? myMath::Constants::PI / 2.0 : -myMath::Constants::PI / 2.0;
            lon = 0.0;
            alt = std::abs( posEcef[2] ) - b;
        }
        else
        {
            const double theta = std::atan2( ( posEcef[2] * myMath::Constants::EARTH_EQUITORIAL_RADIUS ), ( p * b ) );

            lat = std::atan2( posEcef[2] + ep2 * b * std::pow( std::sin( theta ), 3 ), p - ecc2 * myMath::Constants::EARTH_EQUITORIAL_RADIUS * std::pow( std::cos( theta ), 3 ) );
            lon = std::atan2( posEcef[1], posEcef[0] );

            const double N = myMath::Constants::EARTH_EQUITORIAL_RADIUS / std::sqrt( 1.0 - ecc2 * myMath::SQ( std::sin( lat ) ) );
            alt = ( p / std::cos( lat ) ) - N;
        }
    }

    void LlaToEcef( const double lat, const double lon, const double alt, myMath::Vector3d& posEcef )
    {
        // WGS84 constants
        const double ecc2 = myMath::SQ( 8.1819190842622e-2 ); // first eccentricity

        // calculations
        const double N = myMath::Constants::EARTH_EQUITORIAL_RADIUS / std::sqrt( 1.0 - ecc2 * myMath::SQ( std::sin( lat ) ) );
        posEcef[0] = ( N + alt ) * std::cos( lat ) * std::cos( lon );
        posEcef[1] = ( N + alt ) * std::cos( lat ) * std::sin( lon );
        posEcef[2] = ( N * ( 1.0 - ecc2 ) + alt ) * std::sin( lat );
    }

} // namespace WGS84
