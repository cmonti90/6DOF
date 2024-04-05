#ifndef HIGHRATE_DIGITAL_FILTER_BASE_H
#define HIGHRATE_DIGITAL_FILTER_BASE_H

class HighRateDigitalFilterBase
{
  public:
    HighRateDigitalFilterBase()          = default;
    virtual ~HighRateDigitalFilterBase() = default;

    virtual const float* GetNum() const = 0;
    virtual const float* GetDen() const = 0;

    virtual void SetState( const float inState0,
                           const float inState1,
                           const float inState2,
                           const float inState3,
                           const float inState4 ) = 0;

    virtual void SetDefaults() = 0;
    virtual void SetCoefficients( const float* inNum, const float* inDen ) = 0;

    virtual float Update( const float inU) = 0;
};


#endif // HIGHRATE_DIGITAL_FILTER_BASE_H