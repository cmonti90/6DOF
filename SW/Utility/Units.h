#ifndef EED1E22F_0DFF_452F_9A23_9AA2DFD76461
#define EED1E22F_0DFF_452F_9A23_9AA2DFD76461

#include "Constants.h"

namespace Units
{
    static double operator""_kg( const long double val )
    {
        return static_cast<double>( val );
    }

    static double operator""_m( const long double val )
    {
        return static_cast<double>( val );
    }


    static double operator""_km( const long double val )
    {
        return ( 1000.0 * static_cast<double>( val ) );
    }

    static double operator""_rad( const long double val )
    {
        return ( static_cast<double>( val ) );
    }

    static double operator""_deg( const long double val )
    {
        return ( static_cast<double>( val ) * myMath::Constants::DEG_TO_RAD );
    }
}

using namespace Units;

#endif /* EED1E22F_0DFF_452F_9A23_9AA2DFD76461 */
