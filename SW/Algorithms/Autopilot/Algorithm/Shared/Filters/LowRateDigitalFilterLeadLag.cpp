
#include "LowRateDigitalFilterLeadLag.h"

#include "myMathConstants.h"

#include <cmath>

LowRateDigitalFilterLeadLag::LowRateDigitalFilterLeadLag()
    : sampleRate_     ( 0.0f )
    , leadFreq_       ( 0.0f )
    , lagFreq_        ( 0.0f )
    , lagDampingRatio_( 0.0f )
{
    SetDefaults();
}

LowRateDigitalFilterLeadLag::~LowRateDigitalFilterLeadLag()
{
}

const float* LowRateDigitalFilterLeadLag::GetNum() const
{
    return num_;
}

const float* LowRateDigitalFilterLeadLag::GetDen() const
{
    return den_;
}

void LowRateDigitalFilterLeadLag::SetDefaults()
{
    sampleRate_      = 1.0f;
    leadFreq_        = 0.5f;
    lagFreq_         = 0.5f;
    lagDampingRatio_ = 0.0f;

    num_[0] = 0.0f;
    num_[1] = 0.0f;
    num_[2] = 0.0f;

    den_[0] = 0.0f;
    den_[1] = 0.0f;
}

void LowRateDigitalFilterLeadLag::SetParameters( const float params[5] )
{
    leadFreq_        = params[0];
    lagFreq_         = params[1];
    lagDampingRatio_ = params[2];
}

void LowRateDigitalFilterLeadLag::SetSampleRate( const float inSampleRate )
{
    sampleRate_ = inSampleRate;
}

void LowRateDigitalFilterLeadLag::CalculateCoefficients()
{
    float den0;
    float n0, n1, n2;
    float d0, d1, d2;
    float k, k2;

    n0 = 1.0f;
    n1 = 2.0f * lagDampingRatio_ / ( 2.0f * myMath::Constants::PI * leadFreq_ );
    n2 = 1.0f / ( 2.0f * static_cast< float >( myMath::Constants::PI ) * lagFreq_ * 2.0f * static_cast< float >( myMath::Constants::PI ) * lagFreq_ );

    d0 = 1.0f;
    d1 = 2.0f * lagDampingRatio_ / ( 2.0f * myMath::Constants::PI * lagFreq_ );
    d2 = 1.0f / ( 2.0f * static_cast< float >( myMath::Constants::PI ) * lagFreq_ * 2.0f * static_cast< float >( myMath::Constants::PI ) * lagFreq_ );

    k = 2.0f * static_cast< float >( myMath::Constants::PI ) * std::sqrt( leadFreq_ * lagFreq_ )
        / std::tan( static_cast< float >( myMath::Constants::PI ) * std::sqrt( leadFreq_ / sampleRate_ ) / sampleRate_ );
    k2 = k * k;

    den0 =              k2 * d2 + k * d1 +        d0;
    den_[0] = ( -2.0f * k2 * d2          + 2.0f * d0 ) / den0;
    den_[1] = (         k2 * d2 - k * d1 +        d0 ) / den0;

    num_[0] =           k2 * n2 + k * n1 +        n0   / den0;
    num_[1] = ( -2.0f * k2 * n2          + 2.0f * n0 ) / den0;
    num_[2] = (         k2 * n2 - k * n1 +        n0 ) / den0;
}