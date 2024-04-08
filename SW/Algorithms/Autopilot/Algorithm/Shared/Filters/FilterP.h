#ifndef FILTER_P_H
#define FILTER_P_H

#include "HighRateDigitalFilter2.h"
#include "HighRateDigitalFilter4.h"


class FilterP
{
    public:
        FilterP();
        ~FilterP();

        void SetCoefficients( const float* inNumLowPass,
                              const float* inDenLowPass,
                              const float* inNumNotch,
                              const float* inDenNotch,
                              const float* inNumComp,
                              const float* inDenComp );

        float Update( const float inU );

    private:

        HighRateDigitalFilter2 lowPass_;
        HighRateDigitalFilter2 notch_;
        HighRateDigitalFilter2 comp_;

}; // class FilterP

#endif // FILTER_P_H