
#include "LowRateDigitalFilterComp.h"

#include "myMathConstants.h"

LowRateDigitalFilterComp::LowRateDigitalFilterComp()
    : sampleRate_     ( 0.0f )
    , leadFreq_       ( 0.0f )
    , lagFreq_        ( 0.0f )
    , lagDampingRatio_( 0.0f )
{
    SetDefaults();
}

LowRateDigitalFilterComp::~LowRateDigitalFilterComp()
{
}

const float* LowRateDigitalFilterComp::GetNum() const
{
    return num_;
}

const float* LowRateDigitalFilterComp::GetDen() const
{
    return den_;
}

void LowRateDigitalFilterComp::SetDefaults()
{
    sampleRate_      = 1.0f;
    leadFreq_        = 0.5f;
    lagFreq_         = 0.5f;
    lagDampingRatio_ = 0.70710678f;

    num_[0] = 0.0f;
    num_[1] = 0.0f;
    num_[2] = 0.0f;

    den_[0] = 0.0f;
    den_[1] = 0.0f;
}

void LowRateDigitalFilterComp::SetParameters( const float params[5] )
{
    leadFreq_        = params[0];
    lagFreq_         = params[1];
    lagDampingRatio_ = params[2];
}

void LowRateDigitalFilterComp::SetSampleRate( const float inSampleRate )
{
    sampleRate_ = inSampleRate;
}

void LowRateDigitalFilterComp::CalculateCoefficients()
{
    float fN0, fN1, fN2;
    float fD0, fD1, fD2;
    float fK, fK2;
    float fScale;

    float fNum0, fNum1, fNum2;
    float fDen0, fDen1, fDen2;

    fN0 = 1.0f;
    fN1 = 1.0f / ( 2.0f * static_cast< float >( myMath::Constants::PI ) * leadFreq_ );
    fN2 = 0.0f;

    fD0 = 1.0f;
    fD1 = 1.0f * lagDampingRatio_ / ( 2.0f * static_cast< float >( myMath::Constants::PI ) * lagFreq_ );
    fD2 = 1.0f / ( ( 2.0f * static_cast< float >( myMath::Constants::PI ) ) * ( 2.0f * static_cast< float >( myMath::Constants::PI ) * lagFreq_ * lagFreq_ ) );

    fK  = 2.0f * sampleRate_;
    fK2 = fK * fK;

    fNum0 =         fN2 * fK2 + fK * fN1 +        fN0;
    fNum1 = -2.0f * fN2 * fK2            + 2.0f * fN0;
    fNum2 =         fN2 * fK2 - fK * fN1 +        fN0;

    fDen0 =        fD2 * fK2 + fK * fD1 +        fD0;
    fDen1 = -2.0 * fD2 * fK2            + 2.0f * fD0;
    fDen2 =        fD2 * fK2 - fK * fD1 +        fD0;

    fScale = 1.0f / fDen0;

    num_[0] = fNum0 * fScale;
    num_[1] = fNum1 * fScale;
    num_[2] = fNum2 * fScale;

    den_[0] = fDen1 * fScale;
    den_[1] = fDen2 * fScale;

}