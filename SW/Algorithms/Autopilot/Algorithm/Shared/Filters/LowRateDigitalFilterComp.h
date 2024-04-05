#ifndef LOWRATE_DIGITAL_FILTER_COMP_H
#define LOWRATE_DIGITAL_FILTER_COMP_H

#include "LowRateDigitalFilterBase.h"

class LowRateDigitalFilterComp : public LowRateDigitalFilterBase
{
  public:
    
    LowRateDigitalFilterComp();
    virtual ~LowRateDigitalFilterComp();

    float sampleRate_;
    float leadFreq_;
    float lagFreq_;
    float lagDampingRatio_;

    float num_[3];
    float den_[2];

    virtual const float* GetNum() const override;
    virtual const float* GetDen() const override;

    virtual void SetDefaults() override;
    virtual void SetParameters( const float params[5] ) override;
    virtual void SetSampleRate( const float inSampleRate ) override;

    virtual void CalculateCoefficients() override;

}; // class LowRateDigitalFilterComp


#endif // LOWRATE_DIGITAL_FILTER_COMP_H