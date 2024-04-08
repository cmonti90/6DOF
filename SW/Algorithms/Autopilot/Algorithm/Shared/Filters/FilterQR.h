#ifndef FILTER_QR_H
#define FILTER_QR_H

#include "HighRateDigitalFilter2.h"
#include "HighRateDigitalFilter4.h"

class FilterQR
{
  public:
    FilterQR();
    ~FilterQR();

    void SetCoefficients( const float* inNumLowPass,
                          const float* inDenLowPass,
                          const float* inNumNotch1,
                          const float* inDenNotch1,
                          const float* inNumNotch2,
                          const float* inDenNotch2,
                          const float* inNumComp,
                          const float* inDenComp );

    float Update( const float inU );

  private:

    HighRateDigitalFilter2 lowPass_;
    HighRateDigitalFilter2 notch1_;
    HighRateDigitalFilter2 notch2_;
    HighRateDigitalFilter2 comp_;

}; // class FilterQR

#endif // FILTER_QR_H