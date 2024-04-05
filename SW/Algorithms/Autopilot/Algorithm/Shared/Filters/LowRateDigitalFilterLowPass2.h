#ifndef LOWRATE_DIGITAL_FILTER_LOWPASS2_H
#define LOWRATE_DIGITAL_FILTER_LOWPASS2_H

#include "LowRateDigitalFilterBase.h"

class LowRateDigitalFilterLowPass2 : public LowRateDigitalFilterBase
{
  public:
    
    LowRateDigitalFilterLowPass2();
    virtual ~LowRateDigitalFilterLowPass2();

    float sampleRate_;
    float freq_;
    float dampingRatio_;

    float num_[3];
    float den_[2];

    virtual const float* GetNum() const override;
    virtual const float* GetDen() const override;

    virtual void SetDefaults() override;
    virtual void SetParameters( const float params[5] ) override;
    virtual void SetSampleRate( const float inSampleRate ) override;

    virtual void CalculateCoefficients() override;

}; // class LowRateDigitalFilterLowPass2


#endif // LOWRATE_DIGITAL_FILTER_LOWPASS2_H