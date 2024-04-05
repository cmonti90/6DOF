
#include "LowRateDigitalFilterNotch2.h"

#include "myMathConstants.h"

#include <cmath>

LowRateDigitalFilterNotch2::LowRateDigitalFilterNotch2()
    : sampleRate_( 0.0f )
    , notchFreq_ ( 0.0f )
    , zeta_      ( 0.0f )
{
    SetDefaults();
}

LowRateDigitalFilterNotch2::~LowRateDigitalFilterNotch2()
{
}

const float* LowRateDigitalFilterNotch2::GetNum() const
{
    return num_;
}

const float* LowRateDigitalFilterNotch2::GetDen() const
{
    return den_;
}

void LowRateDigitalFilterNotch2::SetDefaults()
{
    sampleRate_ = 1.0f;
    notchFreq_  = 75.0f;
    zeta_       = 10.0f;

    num_[0] = 0.0f;
    num_[1] = 0.0f;
    num_[2] = 0.0f;

    den_[0] = 0.0f;
    den_[1] = 0.0f;
}

void LowRateDigitalFilterNotch2::SetParameters( const float params[5] )
{
    notchFreq_ = params[0];
    zeta_      = params[1] / 20.0f;
}

void LowRateDigitalFilterNotch2::SetSampleRate( const float inSampleRate )
{
    sampleRate_ = inSampleRate;
}

void LowRateDigitalFilterNotch2::CalculateCoefficients()
{
    float omegaA;
    float k, k2, k2p1, twoZetaK, twoK2m1;
    float den0;

    omegaA = 2.0f * sampleRate_ * std::tan( notchFreq_ * static_cast< float >( myMath::Constants::PI ) / sampleRate_ );

    k    = 0.5f * omegaA / sampleRate_;
    k2   = k * k;
    k2p1 = k2 + 1.0f;

    twoZetaK = 2.0f * zeta_ * k;
    twoK2m1  = 2.0f * ( k2 - 1.0f );

    den0    = k2p1 + twoZetaK;
    den_[0] = twoK2m1             / den0;
    den_[1] = ( k2p1 - twoZetaK ) / den0;

    num_[0] = k2p1    / den0;
    num_[1] = twoK2m1 / den0;
    num_[2] = k2p1    / den0;
}