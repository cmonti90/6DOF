#ifndef LOWRATE_DIGITAL_FILTER_BASE_H
#define LOWRATE_DIGITAL_FILTER_BASE_H

class LowRateDigitalFilterBase
{
public:
    LowRateDigitalFilterBase()          = default;
    virtual ~LowRateDigitalFilterBase() = default;
    
    virtual const float* GetNum() const = 0;
    virtual const float* GetDen() const = 0;

    virtual void SetDefaults() = 0;
    virtual void SetParameters( const float params[5] )    = 0;
    virtual void SetSampleRate( const float inSampleRate ) = 0;

    virtual void CalculateCoefficients() = 0;
};


#endif // LOWRATE_DIGITAL_FILTER_BASE_H