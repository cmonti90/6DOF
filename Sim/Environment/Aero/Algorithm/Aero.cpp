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
    airDensity = AeroTables::densityTable.lookUp(inData.altSeaLevel);
    dynamicPressure = 0.5 * airDensity * myMath::SQ(inData.velBody.Magnitude());
    airTempK = AeroTables::temperatureTable.lookUp(inData.altSeaLevel) - 273.15;
    speedOfSound = std::sqrt(myMath::Constants::ADIABATIC_INDEX_AIR * myMath::Constants::UNIVERSAL_GAS_CONST * airTempK / myMath::Constants::MOLAR_MASS_AIR);
    mach = inData.velBody.Magnitude() / speedOfSound;

    updateCoefficients(inData);

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

void Aero::updateCoefficients(const AeroTypes::InData& inData)
{
    updateWingCoefficients(inData);
    updateFuselageCoefficients(inData);
    updateHorizontalTailCoefficients(inData);
    updateVerticalTailCoefficients(inData);
}

void Aero::updateWingCoefficients(const AeroTypes::InData& inData)
{
    wing.C_D = wing.C_D0 + wing.C_Dalpha * myMath::ABS(inData.angleOfAttack) + wing.C_DalphaDot * myMath::ABS(inData.angleOfAttackDot) + wing.C_Dq * myMath::ABS(inData.eulerAngRates[1]);
    wing.C_L = wing.C_L0 + wing.C_Lalpha * inData.angleOfAttack + wing.C_LalphaDot * inData.angleOfAttackDot + wing.C_Lq * inData.eulerAngRates[1];
    wing.C_Y = wing.C_Y0 + wing.C_Ybeta * inData.angleOfSideslip + wing.C_YbetaDot * inData.angleOfSideslipDot + wing.C_Yp * inData.eulerAngRates[0] + wing.C_Yr * inData.eulerAngRates[2];

    wing.C_l = wing.C_l0 + wing.C_lbeta * inData.angleOfSideslip + wing.C_lbetaDot * inData.angleOfSideslipDot + wing.C_lp * inData.eulerAngRates[0] + wing.C_lr * inData.eulerAngRates[2];
    wing.C_m = wing.C_m0 + wing.C_malpha * inData.angleOfAttack + wing.C_malphaDot * inData.angleOfAttackDot + wing.C_mq * inData.eulerAngRates[1];
    wing.C_n = wing.C_n0 + wing.C_nbeta * inData.angleOfSideslip + wing.C_nbetaDot * inData.angleOfSideslipDot + wing.C_np * inData.eulerAngRates[0] + wing.C_nr * inData.eulerAngRates[2];
}

void Aero::updateFuselageCoefficients(const AeroTypes::InData& inData)
{
    fuselage.C_D = fuselage.C_D0 + fuselage.C_Dalpha * myMath::ABS(inData.angleOfAttack - Aircraft::WingIncidenceAngle) + fuselage.C_DalphaDot * myMath::ABS(inData.angleOfAttackDot) + fuselage.C_Dq * myMath::ABS(inData.eulerAngRates[1]);
    fuselage.C_L = fuselage.C_L0 + fuselage.C_Lalpha * (inData.angleOfAttack - Aircraft::WingIncidenceAngle) + fuselage.C_LalphaDot * inData.angleOfAttackDot + fuselage.C_Lq * inData.eulerAngRates[1];
    fuselage.C_Y = fuselage.C_Y0 + fuselage.C_Ybeta * inData.angleOfSideslip + fuselage.C_YbetaDot * inData.angleOfSideslipDot + fuselage.C_Yp * inData.eulerAngRates[0] + fuselage.C_Yr * inData.eulerAngRates[2];

    fuselage.C_l = fuselage.C_l0 + fuselage.C_lbeta * inData.angleOfSideslip + fuselage.C_lbetaDot * inData.angleOfSideslipDot + fuselage.C_lp * inData.eulerAngRates[0] + fuselage.C_lr * inData.eulerAngRates[2];
    fuselage.C_m = fuselage.C_m0 + fuselage.C_malpha * (inData.angleOfAttack - Aircraft::WingIncidenceAngle) + fuselage.C_malphaDot * inData.angleOfAttackDot + fuselage.C_mq * inData.eulerAngRates[1];
    fuselage.C_n = fuselage.C_n0 + fuselage.C_nbeta * inData.angleOfSideslip + fuselage.C_nbetaDot * inData.angleOfSideslipDot + fuselage.C_np * inData.eulerAngRates[0] + fuselage.C_nr * inData.eulerAngRates[2];
}

void Aero::updateHorizontalTailCoefficients(const AeroTypes::InData& inData)
{
    horzTail.C_D = horzTail.C_D0 + horzTail.C_Dalpha * myMath::ABS(inData.angleOfAttack - Aircraft::WingIncidenceAngle) + horzTail.C_DalphaDot * myMath::ABS(inData.angleOfAttackDot) + horzTail.C_Dq * myMath::ABS(inData.eulerAngRates[1]);
    horzTail.C_L = horzTail.C_L0 + horzTail.C_Lalpha * (inData.angleOfAttack - Aircraft::WingIncidenceAngle) + horzTail.C_LalphaDot * inData.angleOfAttackDot + horzTail.C_Lq * inData.eulerAngRates[1];
    horzTail.C_Y = horzTail.C_Y0 + horzTail.C_Ybeta * inData.angleOfSideslip + horzTail.C_YbetaDot * inData.angleOfSideslipDot + horzTail.C_Yp * inData.eulerAngRates[0] + horzTail.C_Yr * inData.eulerAngRates[2];

    horzTail.C_l = horzTail.C_l0 + horzTail.C_lbeta * inData.angleOfSideslip + horzTail.C_lbetaDot * inData.angleOfSideslipDot + horzTail.C_lp * inData.eulerAngRates[0] + horzTail.C_lr * inData.eulerAngRates[2];
    horzTail.C_m = horzTail.C_m0 + horzTail.C_malpha * (inData.angleOfAttack - Aircraft::WingIncidenceAngle) + horzTail.C_malphaDot * inData.angleOfAttackDot + horzTail.C_mq * inData.eulerAngRates[1];
    horzTail.C_n = horzTail.C_n0 + horzTail.C_nbeta * inData.angleOfSideslip + horzTail.C_nbetaDot * inData.angleOfSideslipDot + horzTail.C_np * inData.eulerAngRates[0] + horzTail.C_nr * inData.eulerAngRates[2];
}

void Aero::updateVerticalTailCoefficients(const AeroTypes::InData& inData)
{
    vertTail.C_D = vertTail.C_D0 + vertTail.C_Dalpha * myMath::ABS(inData.angleOfAttack - Aircraft::WingIncidenceAngle) + vertTail.C_DalphaDot * myMath::ABS(inData.angleOfAttackDot) + vertTail.C_Dq * myMath::ABS(inData.eulerAngRates[1]);
    vertTail.C_L = vertTail.C_L0 + vertTail.C_Lalpha * (inData.angleOfAttack - Aircraft::WingIncidenceAngle) + vertTail.C_LalphaDot * inData.angleOfAttackDot + vertTail.C_Lq * inData.eulerAngRates[1];
    vertTail.C_Y = vertTail.C_Y0 + vertTail.C_Ybeta * inData.angleOfSideslip + vertTail.C_YbetaDot * inData.angleOfSideslipDot + vertTail.C_Yp * inData.eulerAngRates[0] + vertTail.C_Yr * inData.eulerAngRates[2];

    vertTail.C_l = vertTail.C_l0 + vertTail.C_lbeta * inData.angleOfSideslip + vertTail.C_lbetaDot * inData.angleOfSideslipDot + vertTail.C_lp * inData.eulerAngRates[0] + vertTail.C_lr * inData.eulerAngRates[2];
    vertTail.C_m = vertTail.C_m0 + vertTail.C_malpha * (inData.angleOfAttack - Aircraft::WingIncidenceAngle) + vertTail.C_malphaDot * inData.angleOfAttackDot + vertTail.C_mq * inData.eulerAngRates[1];
    vertTail.C_n = vertTail.C_n0 + vertTail.C_nbeta * inData.angleOfSideslip + vertTail.C_nbetaDot * inData.angleOfSideslipDot + vertTail.C_np * inData.eulerAngRates[0] + vertTail.C_nr * inData.eulerAngRates[2];
}

void Aero::updateAileronCoefficients(const AeroTypes::InData& inData)
{
    
}

void Aero::computeAeroForces()
{
    F_D = dynamicPressure * (Aircraft::WingArea * wing.C_D + Aircraft::FuselageArea * fuselage.C_D + Aircraft::HorizontalTailArea * horzTail.C_D + Aircraft::VerticalTailArea * vertTail.C_D);
    F_L = dynamicPressure * (Aircraft::WingArea * wing.C_L + Aircraft::FuselageArea * fuselage.C_L + Aircraft::HorizontalTailArea * horzTail.C_L);
    F_Y = dynamicPressure * (Aircraft::WingArea * wing.C_Y + Aircraft::FuselageArea * fuselage.C_Y + Aircraft::HorizontalTailArea * horzTail.C_Y + Aircraft::VerticalTailArea * vertTail.C_Y);

    aeroForceBody = myMath::Vector3d({-F_D, F_Y, F_L});
}

void Aero::computeAeroMoments()
{
    M_l = dynamicPressure * (Aircraft::WingArea * Aircraft::WingSpan * wing.C_l + Aircraft::FuselageArea * Aircraft::FuselageLength * fuselage.C_l + Aircraft::HorizontalTailArea * Aircraft::HorizontalTailSpan * horzTail.C_l + Aircraft::VerticalTailArea * Aircraft::VerticalTailSpan * vertTail.C_l);
    M_m = dynamicPressure * (Aircraft::WingArea * Aircraft::WingMeanChord * wing.C_m + Aircraft::FuselageArea * Aircraft::FuselageLength * fuselage.C_m + Aircraft::HorizontalTailArea * Aircraft::HorizontalTailSpan * horzTail.C_m + Aircraft::VerticalTailArea * Aircraft::VerticalTailMeanChord * vertTail.C_m);
    M_n = dynamicPressure * (Aircraft::WingArea * Aircraft::WingSpan * wing.C_n + Aircraft::FuselageArea * Aircraft::FuselageLength * fuselage.C_n + Aircraft::HorizontalTailArea * Aircraft::HorizontalTailSpan * horzTail.C_n + Aircraft::VerticalTailArea * Aircraft::VerticalTailSpan * vertTail.C_n);
}

