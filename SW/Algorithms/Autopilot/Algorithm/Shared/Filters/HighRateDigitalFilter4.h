#ifndef HIGHRATE_DIGITAL_FILTER4_H
#define HIGHRATE_DIGITAL_FILTER4_H

#include "HighRateDigitalFilterBase.h"

class HighRateDigitalFilter4 : public HighRateDigitalFilterBase
{
  public:
    
    HighRateDigitalFilter4();
    virtual ~HighRateDigitalFilter4();

    float input_;
    float output_;

    float num_[5];
    float den_[4];

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

}; // class HighRateDigitalFilter4


#endif // HIGHRATE_DIGITAL_FILTER4_H
