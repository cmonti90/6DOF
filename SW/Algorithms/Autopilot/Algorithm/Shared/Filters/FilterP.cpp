
#include "FilterP.h"

FilterP::FilterP()
    : lowPass_()
    , notch_  ()
    , comp_   ()
{
}

FilterP::~FilterP()
{
}

void FilterP::SetCoefficients( const float* inNumLowPass,
                               const float* inDenLowPass,
                               const float* inNumNotch,
                               const float* inDenNotch,
                               const float* inNumComp,
                               const float* inDenComp )
{
    lowPass_.SetCoefficients( inNumLowPass, inDenLowPass );
    notch_  .SetCoefficients( inNumNotch, inDenNotch );
    comp_   .SetCoefficients( inNumComp, inDenComp );
}

float FilterP::Update( const float inU )
{
    float outputLowPass = lowPass_.Update( inU );
    float outputNotch   = notch_  .Update( outputLowPass );

    return comp_.Update( outputNotch );
}