
#include "FilterQR.h"

FilterQR::FilterQR()
    : lowPass_()
    , notch1_ ()
    , notch2_ ()
    , comp_   ()
{
}

FilterQR::~FilterQR()
{
}

void FilterQR::SetCoefficients( const float* inNumLowPass,
                                const float* inDenLowPass,
                                const float* inNumNotch1,
                                const float* inDenNotch1,
                                const float* inNumNotch2,
                                const float* inDenNotch2,
                                const float* inNumComp,
                                const float* inDenComp )
{
    lowPass_.SetCoefficients( inNumLowPass, inDenLowPass );
    notch1_ .SetCoefficients( inNumNotch1, inDenNotch1 );
    notch2_ .SetCoefficients( inNumNotch2, inDenNotch2 );
    comp_   .SetCoefficients( inNumComp, inDenComp );
}

float FilterQR::Update( const float inU )
{
    float outputLowPass = lowPass_.Update( inU );
    float outputNotch1  = notch1_ .Update( outputLowPass );
    float outputNotch2  = notch2_ .Update( outputNotch1 );
    
    return comp_.Update( outputNotch2 );
}