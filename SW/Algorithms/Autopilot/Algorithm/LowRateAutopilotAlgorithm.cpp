
#include "LowRateAutopilotAlgorithm.h"

LowRateAutopilotAlgorithm::LowRateAutopilotAlgorithm()
    : azCmd_       ( 0.0f )
    , ayCmd_       ( 0.0f )
    , azCmdLimited_( 0.0f )
    , ayCmdLimited_( 0.0f )

    , u_( 0.0f )
    , v_( 0.0f )
    , w_( 0.0f )

    , aX_( 0.0f )

    , gravity_( {0.0f, 0.0f, 0.0f} )

    , maxG_              ( 0.0f )
    , cmdErrorLimit_     ( 0.0f )
    , acccelCmdRateLimit_( 0.0f )
    , rollCmdErrorLimit_ ( 0.0f )
    , finStallLimit_     ( 0.0f )

    , gains_()

    , ratio_ ( 0.0f )
    , gAngle_( 0.0f )

    , rollLowPassFreq_        ( 0.0f )
    , rollLowPassDampingRatio_( 0.0f )
    , rollCompLeadFreq_       ( 0.0f )
    , rollCompLagFreq_        ( 0.0f )
    , rollCompLagDampingRatio_( 0.0f )
    , rollNotchFreq_          ( 0.0f )
    , rollNotchRipple_        ( 0.0f )
    , rollNotchDepth_         ( 0.0f )
    , rollNotchWidth_         ( 0.0f )

    , lateralLowPassFreq_        ( 0.0f )
    , lateralLowPassDampingRatio_( 0.0f )
    , lateralCompLeadFreq_       ( 0.0f )
    , lateralCompLagFreq_        ( 0.0f )
    , lateralCompLagDampingRatio_( 0.0f )
    , lateralNotch1Freq_         ( 0.0f )
    , lateralNotch1Ripple_       ( 0.0f )
    , lateralNotch1Depth_        ( 0.0f )
    , lateralNotch1Width_        ( 0.0f )
    , lateralNotch2Freq_         ( 0.0f )
    , lateralNotch2Ripple_       ( 0.0f )
    , lateralNotch2Depth_        ( 0.0f )
    , lateralNotch2Width_        ( 0.0f )

    , rollLowPassFilterParameters_()
    , rollCompFilterParameters_   ()
    , rollNotchFilterParameters_  ()

    , lateralLowPassFilterParameters_()
    , lateralCompFilterParameters_   ()
    , lateralNotch1FilterParameters_ ()
    , lateralNotch2FilterParameters_ ()
{
}

LowRateAutopilotAlgorithm::~LowRateAutopilotAlgorithm()
{
}

void LowRateAutopilotAlgorithm::initialize()
{
}

void LowRateAutopilotAlgorithm::process( const LowRateAutopilotTypes::InData& inData, LowRateAutopilotTypes::OutData& outData )
{
}

void LowRateAutopilotAlgorithm::finalize()
{
}
