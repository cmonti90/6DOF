#ifndef HIGHRATE_DIGITAL_FILTER2_H
#define HIGHRATE_DIGITAL_FILTER2_H

#include "HighRateDigitalFilterBase.h"

class HighRateDigitalFilter2 : public HighRateDigitalFilterBase
{
  public:
    
    HighRateDigitalFilter2();
    virtual ~HighRateDigitalFilter2();

    float input_;
    float output_;

    float num_[3];
    float den_[2];

    float state_[5];

    virtual const float* GetNum() const override;
    virtual const float* GetDen() const override;

    virtual void SetState( const float inState0,
                           const float inState1,
                           const float inState2,
                           const float inState3,
                           const float inState4 ) override;

    virtual void SetDefaults() override;
    virtual void SetCoefficients( const float* inNum, const float* inDen ) override;

    virtual float Update( const float inU ) override;

}; // class HighRateDigitalFilter2


#endif // HIGHRATE_DIGITAL_FILTER2_H
