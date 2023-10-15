#include "Aero.h"

#include "PhysicalProperties.h"
#include "AltitudeTables.h"

#include <math.h>

Aero::Aero()
{
}

Aero::~Aero()
{
}

void Aero::initialize()
{

}

void Aero::exec( const AeroTypes::InData& inData, AeroTypes::OutData& outData )
{
    dynamicPressure = 0.5 * inData.density * myMath::SQ( inData.velBody.Magnitude() );
    mach = inData.velBody.Magnitude() / inData.speedOfSound;

    updateCoefficients( inData );

    computeAeroForces();
    computeAeroMoments();

}

void Aero::finalize()
{
    // Do nothing
}

void Aero::BuildOutput( AeroTypes::OutData& outData )
{
    outData.forceBody   = aeroForceBody;
    outData.momentBody  = aeroMomentBody;
}

void Aero::updateCoefficients( const AeroTypes::InData& inData )
{
    // CL0 = 0.4707
    aeroCoefs.C_Lalpha = inData.angleOfAttack*(-3.0576e-6 * std::pow(inData.angleOfAttack, 3) - 7.293e-5 * myMath::SQ(inData.angleOfAttack) - 2.045e-4 * inData.angleOfAttack + 0.1138);
}

void Aero::computeAeroForces()
{
    F_D = dynamicPressure * ( Aircraft::WingArea * wing.C_D + Aircraft::FuselageArea * fuselage.C_D + Aircraft::HorizontalTailArea * horzTail.C_D + Aircraft::VerticalTailArea * vertTail.C_D );
    F_L = dynamicPressure * ( Aircraft::WingArea * wing.C_L + Aircraft::FuselageArea * fuselage.C_L + Aircraft::HorizontalTailArea * horzTail.C_L );
    F_Y = dynamicPressure * ( Aircraft::WingArea * wing.C_Y + Aircraft::FuselageArea * fuselage.C_Y + Aircraft::HorizontalTailArea * horzTail.C_Y + Aircraft::VerticalTailArea * vertTail.C_Y );

    aeroForceBody = myMath::Vector3d( {-F_D, F_Y, F_L} );
}


void Aero::computeAeroMoments()
{
    M_l = dynamicPressure * ( Aircraft::WingArea * Aircraft::WingSpan * wing.C_l + Aircraft::FuselageArea * Aircraft::FuselageLength * fuselage.C_l + Aircraft::HorizontalTailArea * Aircraft::HorizontalTailSpan * horzTail.C_l + Aircraft::VerticalTailArea * Aircraft::VerticalTailSpan * vertTail.C_l );
    M_m = dynamicPressure * ( Aircraft::WingArea * Aircraft::WingMeanChord * wing.C_m + Aircraft::FuselageArea * Aircraft::FuselageLength * fuselage.C_m + Aircraft::HorizontalTailArea * Aircraft::HorizontalTailSpan * horzTail.C_m + Aircraft::VerticalTailArea * Aircraft::VerticalTailMeanChord * vertTail.C_m );
    M_n = dynamicPressure * ( Aircraft::WingArea * Aircraft::WingSpan * wing.C_n + Aircraft::FuselageArea * Aircraft::FuselageLength * fuselage.C_n + Aircraft::HorizontalTailArea * Aircraft::HorizontalTailSpan * horzTail.C_n + Aircraft::VerticalTailArea * Aircraft::VerticalTailSpan * vertTail.C_n );
}

