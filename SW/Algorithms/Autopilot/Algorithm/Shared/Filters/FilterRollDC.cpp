
#include "FilterRollDC.h"

FilterRollDC::FilterRollDC()
    : notch1_       ()
    , notch2_       ()
{
}

FilterRollDC::~FilterRollDC()
{
}

void FilterRollDC::SetCoefficients( const float* inNumNotch1,
                                    const float* inDenNotch1,
                                    const float* inNumNotch2,
                                    const float* inDenNotch2 )
{
    notch1_.SetCoefficients( inNumNotch1, inDenNotch1 );
    notch2_.SetCoefficients( inNumNotch2, inDenNotch2 );
}

float FilterRollDC::Update( const float inU )
{
    float outputNotch1 = notch1_.Update( inU );
    
    return notch2_.Update( outputNotch1 );
}