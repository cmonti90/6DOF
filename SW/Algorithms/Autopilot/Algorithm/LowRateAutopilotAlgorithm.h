#ifndef LowRateAutopilotAlgorithm_H
#define LowRateAutopilotAlgorithm_H

#include "myMath.h"

#include "LowRateAutopilotTypes.h"

#include <memory>

class LowRateDigitalFilterLowPass2;
class LowRateDigitalFilterComp;
class LowRateDigitalFilterNotch2;

class LowRateAutopilotAlgorithm
{
  public:

    LowRateAutopilotAlgorithm();
    virtual ~LowRateAutopilotAlgorithm();

    void process( const LowRateAutopilotTypes::InData& inData, LowRateAutopilotTypes::OutData& outData );
    void finalize();

  protected:

    void ProcessNavigationData( const LowRateAutopilotTypes::InData& inData );

    void CalculateGainsAndLimits( const LowRateAutopilotTypes::InData& inData );

    void LRMTAPGains(const LowRateAutopilotTypes::InData& inData );

    void KssRateCommands( const LowRateAutopilotTypes::InData& inData );

    void LRMTAPLimits();

    void LRMTAPFilters();

    float Orientation( const float angle ) const;

    void BuildOutput( LowRateAutopilotTypes::OutData& outData );

    /////////////////////
    ///   Variables   ///
    /////////////////////
    float azCmd_;        // Guidance Command in AP Z-axis   [G's]
    float ayCmd_;        // Guidance Command in AP Y-axis   [G's]
    float azCmdLimited_; // Guidance Command in AP Z-axis, limited by maxG   [G's]
    float ayCmdLimited_; // Guidance Command in AP Y-axis, limited by maxG   [G's]

    float u_; // Missile velocity in AP X-axis   [m/s]
    float v_; // Missile velocity in AP Y-axis   [m/s]
    float w_; // Missile velocity in AP Z-axis   [m/s]

    float aX_; // Missile acceleration in AP X-axis   [m/s^2]

    myMath::Vector3f gravityAp_; // Gravity vector in AP frame   [m/s^2]

    float maxG_;                // Maximum G limit for the missile      [G's]
    float cmdErrorLimit_;       // Acceleration Error Magnitude Limit   [m/s^2]
    float acccelCmdRateLimit_;  // Acceleration Command Rate Limit      [G/s]
    float rollCmdErrorLimit_;   // Roll Error Magnitude Limit           [rad]
    float finStallLimit_;       // Fin Stall Limit                      [rad]

    APGains gains_;

    float ratio_;  // Flight Condition: Burn Ratio (Normalized CG Position) [-]
    float gAngle_; // Angle of Guidance Commands (in Polar Coordinates)     [rad]
    float timeCons_; // Estimated Autopilot Time Constant                   [s]

    int indexRatio_;    // Ratio Table Look-up Index                    [-]
    int indexAltitude_; // Altitude Table Look-up Index                 [-]
    int indexMach_;     // Mach Table Look-up Index                     [-]
    int indexAlphaRatio_; // Alpha Ratio Table Look-up Index            [-]
    int indexBetaRatio_;  // Beta Ratio Table Look-up Index             [-]
    int indexAngle_;      // Angle Table Look-up Index                  [-]
    float scaleRatio_;    // Ratio Table Look-up Scale Factors          [-]
    float scaleAltitude_; // Altitude Table Look-up Scale Factors       [-]
    float scaleMach_;     // Mach Table Look-up Scale Factors           [-]
    float scaleAlphaRatio_; // Alpha Ratio Table Look-up Scale Factors  [-]
    float scaleBetaRatio_;  // Beta Ratio Table Look-up Scale Factors   [-]
    float scaleAngle_;      // Angle Table Look-up Scale Factors        [-]

    float rollLowPassFreq_;         // Roll Low Pass Filter Frequency               [Hz]
    float rollLowPassDampingRatio_; // Roll Low Pass Filter Damping Ratio           [-]
    float rollCompLeadFreq_;        // Roll Compensation Lead Filter Frequency      [Hz]
    float rollCompLagFreq_;         // Roll Compensation Lag Filter Frequency       [Hz]
    float rollCompLagDampingRatio_; // Roll Compensation Lag Filter Damping Ratio   [-]
    float rollNotchFreq_;           // Roll Notch Filter Frequency                  [Hz]
    float rollNotchRipple_;         // Roll Notch Filter Ripple                     [dB]
    float rollNotchDepth_;          // Roll Notch Filter Depth                      [dB]
    float rollNotchWidth_;          // Roll Notch Filter Width                      [%]

    float lateralLowPassFreq_;         // Lateral Low Pass Filter Frequency               [Hz]
    float lateralLowPassDampingRatio_; // Lateral Low Pass Filter Damping Ratio           [-]
    float lateralCompLeadFreq_;        // Lateral Compensation Lead Filter Frequency      [Hz]
    float lateralCompLagFreq_;         // Lateral Compensation Lag Filter Frequency       [Hz]
    float lateralCompLagDampingRatio_; // Lateral Compensation Lag Filter Damping Ratio   [-]
    float lateralNotch1Freq_;          // Lateral Notch Filter 1 Frequency                [Hz]
    float lateralNotch1Ripple_;        // Lateral Notch Filter 1 Ripple                   [dB]
    float lateralNotch1Depth_;         // Lateral Notch Filter 1 Depth                    [dB]
    float lateralNotch1Width_;         // Lateral Notch Filter 1 Width                    [%]
    float lateralNotch2Freq_;          // Lateral Notch Filter 2 Frequency                [Hz]
    float lateralNotch2Ripple_;        // Lateral Notch Filter 2 Ripple                   [dB]
    float lateralNotch2Depth_;         // Lateral Notch Filter 2 Depth                    [dB]
    float lateralNotch2Width_;         // Lateral Notch Filter 2 Width                    [%]

    float rollLowPassFilterParameters_[5]; // Roll Low Pass Filter Parameters
    float rollCompFilterParameters_   [5]; // Roll Compensation Filter Parameters
    float rollNotchFilterParameters_  [5]; // Roll Notch Filter Parameters

    float lateralLowPassFilterParameters_[5]; // Lateral Low Pass Filter Parameters
    float lateralCompFilterParameters_   [5]; // Lateral Compensation Filter Parameters
    float lateralNotch1FilterParameters_ [5]; // Lateral Notch Filter 1 Parameters
    float lateralNotch2FilterParameters_ [5]; // Lateral Notch Filter 2 Parameters


    std::unique_ptr< LowRateDigitalFilterLowPass2 > rollLowPassFilter_; // Class with Low Filter Coefficient Look-up Routines
    std::unique_ptr< LowRateDigitalFilterComp     > rollCompFilter_;    // Class with Compensation Filter Coefficient Look-up Routines
    std::unique_ptr< LowRateDigitalFilterNotch2   > rollNotchFilter_;   // Class with Notch Filter Coefficient Look-up Routines

    std::unique_ptr< LowRateDigitalFilterLowPass2 > lateralLowPassFilter_; // Class with Low Filter Coefficient Look-up Routines
    std::unique_ptr< LowRateDigitalFilterComp     > lateralCompFilter_;    // Class with Compensation Filter Coefficient Look-up Routines
    std::unique_ptr< LowRateDigitalFilterNotch2   > lateralNotch1Filter_;  // Class with Notch Filter 1 Coefficient Look-up Routines
    std::unique_ptr< LowRateDigitalFilterNotch2   > lateralNotch2Filter_;  // Class with Notch Filter 2 Coefficient Look-up Routines


  private:

    LowRateAutopilotAlgorithm( const LowRateAutopilotAlgorithm& )               = delete;
    LowRateAutopilotAlgorithm& operator=( const LowRateAutopilotAlgorithm& )    = delete;

};

#endif // LowRateAutopilotAlgorithm_H
