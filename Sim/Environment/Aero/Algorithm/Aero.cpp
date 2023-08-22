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

void Aero::exec(const AeroTypes::InData& inData, AeroTypes::OutData& outData)
{
    // airDensity = AeroTables::densityTable.lookUp(altSeaLevel);
    dynamicPressure = 0.5 * airDensity * myMath::SQ(velT);

    updateCoefficients();

    computeAeroForces();
    computeAeroMoments();

}

void Aero::finalize()
{
    // Do nothing
}

void Aero::BuildOutput(AeroTypes::OutData& outData)
{
    outData.forceBody = aeroForceBody;
    outData.momentBody = aeroMomentBody;
}

void Aero::updateCoefficients()
{

}

void Aero::computeAeroForces()
{
    F_D = dynamicPressure * Aircraft::WingArea * C_D;
    F_L = dynamicPressure * Aircraft::WingArea * C_L;
    F_Y = dynamicPressure * Aircraft::WingArea * C_Y;
}

void Aero::computeAeroMoments()
{
    M_l = dynamicPressure * Aircraft::WingArea * Aircraft::WingSpan * C_l;
    M_m = dynamicPressure * Aircraft::WingArea * Aircraft::WingMeanChord * C_m;
    M_n = dynamicPressure * Aircraft::WingArea * Aircraft::WingSpan * C_n;
}

