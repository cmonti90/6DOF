#ifndef E310DEA6_9F7E_4DEE_9019_DA65A6CAB980
#define E310DEA6_9F7E_4DEE_9019_DA65A6CAB980

namespace Aircraft
{
    static constexpr double WingArea = 50.0; // m^2 (S)
    static constexpr double WingSpan = 10.0; // m (b)
    static constexpr double WingChord = 5.0; // m (c)
    static constexpr double WingMeanChord = 5.0; // m (c_bar)
    static constexpr double WingAspectRatio = WingSpan / WingChord;
    static constexpr double WingTaperRatio = 0.5;
    static constexpr double WingSweepAngle = 0.0; // rad (Lambda)
    static constexpr double WingDihedralAngle = 0.0; // rad (Gamma)
    static constexpr double WingTwistAngle = 0.0; // rad (epsilon)
    static constexpr double WingIncidenceAngle = 0.0; // rad (alpha_0)
    static constexpr double WingZeroLiftAngle = 0.0; // rad (alpha_L0)
    static constexpr double WingLiftCurveSlope = 0.0; // rad^-1 (a)
    static constexpr double WingLiftCurveSlopeAtRoot = 0.0; // rad^-1 (a_0)
    static constexpr double WingLiftCurveSlopeAtTip = 0.0; // rad^-1 (a_1)
    static constexpr double WingLiftCurveSlopeAtMAC = 0.0; // rad^-1 (a_M)
    static constexpr double WingLiftCurveSlopeAtY = 0.0; // rad^-1 (a_y)
    static constexpr double WingLiftCurveSlopeAtZ = 0.0; // rad^-1 (a_z)
    static constexpr double WingLiftCurveSlopeAtX = 0.0; // rad^-1 (a_x)
}

#endif /* E310DEA6_9F7E_4DEE_9019_DA65A6CAB980 */
