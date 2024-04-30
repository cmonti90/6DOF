#ifndef HighRateAutopilotAlgorithm_H
#define HighRateAutopilotAlgorithm_H

#include "HighRateAutopilotTypes.h"

#include "myMath.h"

#include <memory>


class FilterP;
class FilterQR;
class FilterQR;
class FilterRollDC;


class HighRateAutopilotAlgorithm
{
  public:

    HighRateAutopilotAlgorithm();
    virtual ~HighRateAutopilotAlgorithm();

    void process( const HighRateAutopilotTypes::InData& inData, HighRateAutopilotTypes::OutData& outData );
    void finalize();

  protected:

    void ExecuteControlLaw( const HighRateAutopilotTypes::InData& inData );

    void ProcessImuData( const HighRateAutopilotTypes::InData& inData );

    void ProcessGuidanceCommands( const HighRateAutopilotTypes::InData& inData );

    void BuildOutput( HighRateAutopilotTypes::OutData& outData );

    float u_;                    // Missile velocity in AP X-axis       [m/s]
    float v_;                    // Missile velocity in AP Y-axis       [m/s]
    float w_;                    // Missile velocity in AP Z-axis       [m/s]

    float aX_;                   // Missile acceleration in AP X-axis   [m/s^2]
    float aY_;                   // Missile acceleration in AP Y-axis   [m/s^2]
    float aZ_;                   // Missile acceleration in AP Z-axis   [m/s^2]

    myMath::Vector3f gravityAp_; // Gravity vector in AP frame          [m/s^2]

    float maxG_;                 // Guidance Command Magnitude Limit    [G's]
    float accelCmdRateLimit_;    // Guidance Command Rate Limit         [G's/s]
    float cmdErrorLimit_;        // Acceleration Error Magnitude Limit  [G's]
    float rollCmdErrorLimit_;    // Roll Command Error Magnitude Limit  [rad]
    float finStallLimit_;        // Fin Stall Limit                     [rad]

    APGains apGains_;            // Autopilot Gains

    float integratedRollRate_;   // Integrated Roll Rate                [rad]
    float integratedRollRateGuidance_;   // Integrated Roll Rate at last guidance update [rad]
    float cmdRollRateLimited_;   // Rate limited roll command            [rad/s]
    float cmdRoll_;              // Commanded Roll Angle                [rad]

    bool adaptGLimits_;           // Adapt G Limits flag                 [-]

    float maxGSF_;               // GLimit scale factor used in adaptive glimit algorithms   [-]
    int   ctrlPref_;             // Control Preference flag             [-]

    myMath::Vector3f navVel_;    // Velocity in Navigation Frame        [m/s]

    float p_;                    // Rotation Rate in AP X-Axis          [rad/s]
    float q_;                    // Rotation Rate in AP Y-Axis          [rad/s]
    float r_;                    // Rotation Rate in AP Z-Axis          [rad/s]

    float pFiltered_;            // Filtered Rotation Rate in AP X-Axis [rad/s]
    float qFiltered_;            // Filtered Rotation Rate in AP Y-Axis [rad/s]
    float rFiltered_;            // Filtered Rotation Rate in AP Z-Axis [rad/s]

    float deltaRoll_;            // Change in roll since guidance commands [rad]
    float cosDeltaRoll_;         // Cosine of delta roll                 [-]
    float sinDeltaRoll_;         // Sine of delta roll                   [-]

    float rateLimitedRollCmd_;   // Rate limited roll command            [rad]

    float ayCmd_;                // Commanded acceleration in AP Y-Axis [G's]
    float azCmd_;                // Commanded acceleration in AP Z-Axis [G's]
    float cmdMagGs_;             // Magnitude of the commanded acceleration [G's]
    float ayCmdLimited_;         // MaxG Limited commanded acceleration in AP Y-Axis [G's]
    float azCmdLimited_;         // MaxG Limited commanded acceleration in AP Z-Axis [G's]
    float ayCmdRateLimited_;     // Rate limited commanded acceleration in AP Y-Axis [G's]
    float azCmdRateLimited_;     // Rate limited commanded acceleration in AP Z-Axis [G's]

    float ayCmdRotated_;         // Y-Axis accleration command rorated thourgh "deltaRoll_" [G's]
    float azCmdRotated_;         // Z-Axis accleration command rorated thourgh "deltaRoll_" [G's]

    float rollError_;            // Roll Error                           [rad]
    float rollErrorLimited_;     // Limited Roll Error                   [rad]

    float azError_;              // Acceleration Error in AP Z-Axis      [G's]
    float ayError_;              // Acceleration Error in AP Y-Axis      [G's]
    float cmdErrorMag_;          // Magnitude of the acceleration error  [G's]
    float azErrorLimited_;       // Limited Acceleration Error in AP Z-Axis [G's]
    float ayErrorLimited_;       // Limited Acceleration Error in AP Y-Axis [G's]

    float uRate_;                // Rate of change of missile velocity in AP X-Axis [m/s^2]
    float vRate_;                // Rate of change of missile velocity in AP Y-Axis [m/s^2]
    float wRate_;                // Rate of change of missile velocity in AP Z-Axis [m/s^2]
    float alphaDot_;             // Rate of change of angle of attack     [rad/s]
    float betaDot_;              // Rate of change of sideslip angle      [rad/s]

    float rollDecoupling_;       // Roll decoupling signal                [rad/s]
    float rollDecouplingFiltered_; // Filtered roll decoupling signal     [rad/s]

    float pCmd_;                 // Commanded roll rate                   [rad/s]
    float qCmd_;                 // Commanded pitch rate                  [rad/s]
    float rCmd_;                 // Commanded yaw rate                    [rad/s]

    float pCmdFiltered_;         // Filtered Commanded roll rate          [rad/s]
    float qCmdFiltered_;         // Filtered Commanded pitch rate         [rad/s]
    float rCmdFiltered_;         // Filtered Commanded yaw rate           [rad/s]

    float integratorPInput_;     // Roll Integrator Input                 [rad/s]
    float integratorQInput_;     // Pitch Integrator Input                [rad/s]
    float integratorRInput_;     // Yaw Integrator Input                  [rad/s]

    float integratorP_;          // Roll Integrator                       [rad]
    float integratorQ_;          // Pitch Integrator                      [rad]
    float integratorR_;          // Yaw Integrator                        [rad]

    float rollDeflCmd_;          // Commanded roll deflection             [rad]
    float pitchDeflCmd_;         // Commanded pitch deflection            [rad]
    float yawDeflCmd_;           // Commanded yaw deflection              [rad]

    float rollDeflCmdDecoupled_; // Commanded roll deflection, decoupled  [rad]
    float pitchDeflCmdDecoupled_;// Commanded pitch deflection, decoupled [rad]
    float yawDeflCmdDecoupled_;  // Commanded yaw deflection, decoupled   [rad]

    float maxDefl_;              // Maximum deflection limit              [rad]

    bool antiWindup_;            // Flag to test if integrators need resetting [-]

    float rollDeflCmdDecLimited_;   // Limited commanded roll deflection, decoupled  [rad]
    float pitchDeflCmdDecLimited_;  // Limited commanded pitch deflection, decoupled [rad]
    float yawDeflCmdDecLimited_;    // Limited commanded yaw deflection, decoupled   [rad]

    float rollDeflCmdLtdPreMSFR_;  // Limited commanded roll deflection, decoupled, pre MSFR [rad]
    float pitchDeflCmdLtdPreMSFR_; // Limited commanded pitch deflection, decoupled, pre MSFR [rad]
    float yawDeflCmdLtdPreMSFR_;   // Limited commanded yaw deflection, decoupled, pre MSFR [rad]

    float fin1Cmd_;              // Commanded deflection of fin 1 in AP coordinates [rad]
    float fin2Cmd_;              // Commanded deflection of fin 2 in AP coordinates [rad]
    float fin3Cmd_;              // Commanded deflection of fin 3 in AP coordinates [rad]
    float fin4Cmd_;              // Commanded deflection of fin 4 in AP coordinates [rad]

    float scsDelta1Cmd_;        // Commanded for fin 1 in CAS coordinates [rad]
    float scsDelta2Cmd_;        // Commanded for fin 2 in CAS coordinates [rad]
    float scsDelta3Cmd_;        // Commanded for fin 3 in CAS coordinates [rad]
    float scsDelta4Cmd_;        // Commanded for fin 4 in CAS coordinates [rad]

    std::unique_ptr< FilterP      > filterP_;      // Filter for roll rate                   [-]
    std::unique_ptr< FilterQR     > filterQ_;      // Filter for pitch rate                  [-]
    std::unique_ptr< FilterQR     > filterR_;      // Filter for yaw rate                    [-]
    std::unique_ptr< FilterRollDC > filterRollDC_; // Filter for roll rate decoupling        [-]
    std::unique_ptr< FilterQR     > filterQCmd_;   // Filter for pitch rate                  [-]
    std::unique_ptr< FilterQR     > filterRCmd_;   // Filter for yaw rate                    [-]

    bool firstPass_;            // Flag to indicate first pass           [-]

    float sysIdEnable_;               // Flag to enable system identification  [-]
    float sysIdMag_;                  // Frequency sweep magnitude             [deg]
    float sysIdDuration;              // Duration of frequency sweep           [s]
    float sysIdChirpDuration_;        // Duration of chirp                     [s]
    float sysIdDelay_;                // Delay between frequency sweeps        [s]
    float sysIdFreq_;                 // Start frequency of chirp              [Hz]
    float sysIdChannel_;
    float sysIdChirp_;
    float sysIdFreqStart_;
    float sysIdFreqEnd_;

  private:

    void ApplySysIdInput( const HighRateAutopilotTypes::InData& inData );

    HighRateAutopilotAlgorithm( const HighRateAutopilotAlgorithm& ) = delete;
    HighRateAutopilotAlgorithm& operator=( const HighRateAutopilotAlgorithm& ) = delete;

};

#endif // HighRateAutopilotAlgorithm_H
