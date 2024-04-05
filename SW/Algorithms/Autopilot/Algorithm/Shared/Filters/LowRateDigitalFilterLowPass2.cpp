
#include "LowRateDigitalFilterLowPass2.h"

#include "myMathConstants.h"

#include <cmath>

LowRateDigitalFilterLowPass2::LowRateDigitalFilterLowPass2()
    : sampleRate_  ( 0.0f )
    , freq_        ( 0.0f )
    , dampingRatio_( 0.0f )
{
    SetDefaults();
}

LowRateDigitalFilterLowPass2::~LowRateDigitalFilterLowPass2()
{
}

const float* LowRateDigitalFilterLowPass2::GetNum() const
{
    return num_;
}

const float* LowRateDigitalFilterLowPass2::GetDen() const
{
    return den_;
}

void LowRateDigitalFilterLowPass2::SetDefaults()
{
    sampleRate_   = 1.0f;
    freq_         = 0.5f;
    dampingRatio_ = 0.70710678f;

    num_[0] = 0.0f;
    num_[1] = 0.0f;
    num_[2] = 0.0f;

    den_[0] = 0.0f;
    den_[1] = 0.0f;
}

void LowRateDigitalFilterLowPass2::SetParameters( const float params[5] )
{
    freq_         = params[0];
    dampingRatio_ = params[1];
}

void LowRateDigitalFilterLowPass2::SetSampleRate( const float inSampleRate )
{
    sampleRate_ = inSampleRate;
}

void LowRateDigitalFilterLowPass2::CalculateCoefficients()
{
    float den0;
    float fD0, fD1, fD2;
    float fK, fK2;
    float fOmegaA;

    fOmegaA = 2.0f * sampleRate_ * std::tan( static_cast< float >( myMath::Constants::PI ) * freq_ / sampleRate_ );

    fD0 = 1.0f;
    fD1 = 2.0f * dampingRatio_ / fOmegaA;
    fD2 = 1.0f / ( fOmegaA * fOmegaA );

    fK = 2.0f * sampleRate_;
    fK2 = fK * fK;

    den0    =           fK2 * fD2 + fK * fD1 +        fD0;
    den_[0] = ( -2.0f * fK2 * fD2            + 2.0f * fD0 ) / den0;
    den_[1] = (         fK2 * fD2 - fK * fD1 +        fD0 ) / den0;

    num_[0] = 1.0f / den0;
    num_[1] = 2.0f / den0;
    num_[2] = 1.0f / den0;
}