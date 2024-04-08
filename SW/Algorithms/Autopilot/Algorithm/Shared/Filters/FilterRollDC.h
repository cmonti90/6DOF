#ifndef FILTER_ROLL_DC_H
#define FILTER_ROLL_DC_H

#include "HighRateDigitalFilter2.h"
#include "HighRateDigitalFilter4.h"

class FilterRollDC
{
    public:
        FilterRollDC();
        ~FilterRollDC();

        void SetCoefficients( const float* inNumNotch1,
                              const float* inDenNotch1,
                              const float* inNumNotch2,
                              const float* inDenNotch2 );

        float Update( const float inU );

    private:

        HighRateDigitalFilter2 notch1_;
        HighRateDigitalFilter2 notch2_;

}; // class FilterRollDC

#endif // FILTER_ROLL_DC_H