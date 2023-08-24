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
    C_Dw = CDw_0 + CDw_alpha * myMath::ABS(inData.angleOfAttack) + CDw_alphaDot * myMath::ABS(inData.angleOfAttackDot) + CDw_q * myMath::ABS(inData.eulerAngRates[1]) + CDw_deltaE * myMath::ABS(inData.elevatorDefl) + CDw_deltaA * (myMath::ABS(inData.aileronDefl[0]) + myMath::ABS(inData.aileronDefl[1])) + CDw_deltaR * myMath::ABS(inData.rudderDefl) + CDw_deltaT * myMath::ABS(inData.throttle);
    C_Lw = CLw_0 + CLw_alpha * inData.angleOfAttack + CLw_alphaDot * inData.angleOfAttackDot + CLw_q * inData.eulerAngRates[1] + CLw_deltaE * inData.elevatorDefl + CLw_deltaA * (inData.aileronDefl[0] + inData.aileronDefl[1]) + CLw_deltaR * inData.rudderDefl + CLw_deltaT * inData.throttle;
    C_Yw = CYw_0 + CYw_beta * inData.angleOfSideslip + CYw_betaDot * inData.angleOfSideslipDot + CYw_p * inData.eulerAngRates[0] + CYw_r * inData.eulerAngRates[2] + CYw_deltaA * (inData.aileronDefl[0] - inData.aileronDefl[1]) + CYw_deltaR * inData.rudderDefl + CYw_deltaT * inData.throttle;

    C_lw = Clw_0 + Clw_beta * inData.angleOfSideslip + Clw_betaDot * inData.angleOfSideslipDot + Clw_p * inData.eulerAngRates[0] + Clw_r * inData.eulerAngRates[2] + Clw_deltaA * (inData.aileronDefl[0] - inData.aileronDefl[1]) + Clw_deltaR * inData.rudderDefl + Clw_deltaT * inData.throttle;
    C_mw = Cmw_0 + Cmw_alpha * inData.angleOfAttack + Cmw_alphaDot * inData.angleOfAttackDot + Cmw_q * inData.eulerAngRates[1] + Cmw_deltaE * inData.elevatorDefl + Cmw_deltaA * inData.aileronDefl[0] + Cmw_deltaR * inData.rudderDefl + Cmw_deltaT * inData.throttle;
    C_nw = Cnw_0 + Cnw_beta * inData.angleOfSideslip + Cnw_betaDot * inData.angleOfSideslipDot + Cnw_p * inData.eulerAngRates[0] + Cnw_r * inData.eulerAngRates[2] + Cnw_deltaA * (inData.aileronDefl[0] - inData.aileronDefl[1]) + Cnw_deltaR * inData.rudderDefl + Cnw_deltaT * inData.throttle;
}

void Aero::updateFuselageCoefficients(const AeroTypes::InData& inData)
{
    C_Df = CDf_0 + CDf_alpha * myMath::ABS(inData.angleOfAttack) + CDf_alphaDot * myMath::ABS(inData.angleOfAttackDot) + CDf_q * myMath::ABS(inData.eulerAngRates[1]);
    C_Lf = CLf_0 + CLf_alpha * inData.angleOfAttack + CLf_alphaDot * inData.angleOfAttackDot + CLf_q * inData.eulerAngRates[1];
    C_Yf = CYf_0 + CYf_beta * inData.angleOfSideslip + CYf_betaDot * inData.angleOfSideslipDot + CYf_p * inData.eulerAngRates[0] + CYf_r * inData.eulerAngRates[2];

    C_lf = Clf_0 + Clf_beta * inData.angleOfSideslip + Clf_betaDot * inData.angleOfSideslipDot + Clf_p * inData.eulerAngRates[0] + Clf_r * inData.eulerAngRates[2];
    C_mf = Cmf_0 + Cmf_alpha * inData.angleOfAttack + Cmf_alphaDot * inData.angleOfAttackDot + Cmf_q * inData.eulerAngRates[1];
    C_nf = Cnf_0 + Cnf_beta * inData.angleOfSideslip + Cnf_betaDot * inData.angleOfSideslipDot + Cnf_p * inData.eulerAngRates[0] + Cnf_r * inData.eulerAngRates[2];
}

void Aero::updateHorizontalTailCoefficients(const AeroTypes::InData& inData)
{
    C_Dht = CDht_0 + CDht_alpha * myMath::ABS(inData.angleOfAttack) + CDht_alphaDot * myMath::ABS(inData.angleOfAttackDot) + CDht_q * myMath::ABS(inData.eulerAngRates[1]);
    C_Lht = CLht_0 + CLht_alpha * inData.angleOfAttack + CLht_alphaDot * inData.angleOfAttackDot + CLht_q * inData.eulerAngRates[1];
    C_Yht = CYht_0 + CYht_beta * inData.angleOfSideslip + CYht_betaDot * inData.angleOfSideslipDot + CYht_p * inData.eulerAngRates[0] + CYht_r * inData.eulerAngRates[2];

    C_lht = Clht_0 + Clht_beta * inData.angleOfSideslip + Clht_betaDot * inData.angleOfSideslipDot + Clht_p * inData.eulerAngRates[0] + Clht_r * inData.eulerAngRates[2];
    C_mht = Cmht_0 + Cmht_alpha * inData.angleOfAttack + Cmht_alphaDot * inData.angleOfAttackDot + Cmht_q * inData.eulerAngRates[1];
    C_nht = Cnht_0 + Cnht_beta * inData.angleOfSideslip + Cnht_betaDot * inData.angleOfSideslipDot + Cnht_p * inData.eulerAngRates[0] + Cnht_r * inData.eulerAngRates[2];
}

void Aero::updateVerticalTailCoefficients(const AeroTypes::InData& inData)
{
    C_Dvt = CDvt_0 + CDvt_alpha * myMath::ABS(inData.angleOfAttack) + CDvt_alphaDot * myMath::ABS(inData.angleOfAttackDot) + CDvt_q * myMath::ABS(inData.eulerAngRates[1]);
    C_Lvt = CLvt_0 + CLvt_alpha * inData.angleOfAttack + CLvt_alphaDot * inData.angleOfAttackDot + CLvt_q * inData.eulerAngRates[1];
    C_Yvt = CYvt_0 + CYvt_beta * inData.angleOfSideslip + CYvt_betaDot * inData.angleOfSideslipDot + CYvt_p * inData.eulerAngRates[0] + CYvt_r * inData.eulerAngRates[2];

    C_lvt = Clvt_0 + Clvt_beta * inData.angleOfSideslip + Clvt_betaDot * inData.angleOfSideslipDot + Clvt_p * inData.eulerAngRates[0] + Clvt_r * inData.eulerAngRates[2];
    C_mvt = Cmvt_0 + Cmvt_alpha * inData.angleOfAttack + Cmvt_alphaDot * inData.angleOfAttackDot + Cmvt_q * inData.eulerAngRates[1];
    C_nvt = Cnvt_0 + Cnvt_beta * inData.angleOfSideslip + Cnvt_betaDot * inData.angleOfSideslipDot + Cnvt_p * inData.eulerAngRates[0] + Cnvt_r * inData.eulerAngRates[2];
}

void Aero::computeAeroForces()
{
    F_D = dynamicPressure * (Aircraft::WingArea * C_Dw + Aircraft::FuselageArea * C_Df + Aircraft::HorziontalTailArea * C_Dht + Aircraft::VerticalTailArea * C_Dvt);
    F_L = dynamicPressure * (Aircraft::WingArea * C_Lw + Aircraft::FuselageArea * C_Lf + Aircraft::HorziontalTailArea * C_Lht);
    F_Y = dynamicPressure * (Aircraft::WingArea * C_Yw + Aircraft::FuselageArea * C_Yf + Aircraft::HorziontalTailArea * C_Yht + Aircraft::VerticalTailArea * C_Yvt);
}

void Aero::computeAeroMoments()
{
    M_l = dynamicPressure * (Aircraft::WingArea * Aircraft::WingSpan * C_l + Aircraft::FuselageArea * Aircraft::FuselageLength * C_lf +  * Aircraft::HorziontalTailArea * Aircraft::HorziontalTailSpan * C_lht +  * Aircraft::VerticalTailArea * Aircraft::VerticalTailSpan * C_lvt);
    M_m = dynamicPressure * (Aircraft::WingArea * Aircraft::WingMeanChord * C_m + Aircraft::FuselageArea * Aircraft::FuselageLength * C_mf + Aircraft::HorziontalTailArea * Aircraft::HorziontalTailMeanChord * C_mht + Aircraft::VerticalTailArea * Aircraft::VerticalTailMeanChord * C_mvt);
    M_n = dynamicPressure * (Aircraft::WingArea * Aircraft::WingSpan * C_n + Aircraft::FuselageArea * Aircraft::FuselageLength * C_nf + Aircraft::HorziontalTailArea * Aircraft::HorziontalTailSpan * C_nht + Aircraft::VerticalTailArea * Aircraft::VerticalTailSpan * C_nvt);
}

