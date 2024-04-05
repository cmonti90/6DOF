#ifndef LOWRATE_DIGITAL_FILTER_NOTCH2_H
#define LOWRATE_DIGITAL_FILTER_NOTCH2_H

#include "LowRateDigitalFilterBase.h"

class LowRateDigitalFilterNotch2 : public LowRateDigitalFilterBase
{
  public:
    
    LowRateDigitalFilterNotch2();
    virtual ~LowRateDigitalFilterNotch2();

    float sampleRate_;
    float notchFreq_;
    float zeta_;

    float num_[3];
    float den_[2];

    virtual const float* GetNum() const override;
    virtual const float* GetDen() const override;

    virtual void SetDefaults() override;
    virtual void SetParameters( const float params[5] ) override;
    virtual void SetSampleRate( const float inSampleRate ) override;

    virtual void CalculateCoefficients() override;

}; // class LowRateDigitalFilterNotch2


#endif // LOWRATE_DIGITAL_FILTER_NOTCH2_H