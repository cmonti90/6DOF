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

    static constexpr double FuselageArea = 10.0; // m^2 (S_f)
    static constexpr double FuselageLength = 10.0; // m (l_f)
    static constexpr double FuselageDiameter = 5.0; // m (d_f)
    static constexpr double FuselageFinenessRatio = FuselageLength / FuselageDiameter;
    static constexpr double FuselageWettedArea = 0.0; // m^2 (S_wet_f)
    static constexpr double FuselageZeroLiftAngle = 0.0; // rad (alpha_0_f)
    static constexpr double FuselageLiftCurveSlope = 0.0; // rad^-1 (a_f)
    static constexpr double FuselageLiftCurveSlopeAtY = 0.0; // rad^-1 (a_y_f)
    static constexpr double FuselageLiftCurveSlopeAtZ = 0.0; // rad^-1 (a_z_f)
    static constexpr double FuselageLiftCurveSlopeAtX = 0.0; // rad^-1 (a_x_f)

    static constexpr double HorizontalTailArea = 10.0; // m^2 (S_h)
    static constexpr double HorizontalTailSpan = 5.0; // m (b_h)
    static constexpr double HorizontalTailChord = 5.0; // m (c_h)
    static constexpr double HorizontalTailMeanChord = 5.0; // m (c_bar_h)
    static constexpr double HorizontalTailAspectRatio = HorizontalTailSpan / HorizontalTailChord;
    static constexpr double HorizontalTailTaperRatio = 0.5;
    static constexpr double HorizontalTailSweepAngle = 0.0; // rad (Lambda_h)
    static constexpr double HorizontalTailDihedralAngle = 0.0; // rad (Gamma_h)
    static constexpr double HorizontalTailTwistAngle = 0.0; // rad (epsilon_h)
    static constexpr double HorizontalTailIncidenceAngle = 0.0; // rad (alpha_0_h)
    static constexpr double HorizontalTailZeroLiftAngle = 0.0; // rad (alpha_L0_h)
    static constexpr double HorizontalTailLiftCurveSlope = 0.0; // rad^-1 (a_h)
    static constexpr double HorizontalTailLiftCurveSlopeAtRoot = 0.0; // rad^-1 (a_0_h)
    static constexpr double HorizontalTailLiftCurveSlopeAtTip = 0.0; // rad^-1 (a_1_h)
    static constexpr double HorizontalTailLiftCurveSlopeAtMAC = 0.0; // rad^-1 (a_M_h)
    static constexpr double HorizontalTailLiftCurveSlopeAtY = 0.0; // rad^-1 (a_y_h)
    static constexpr double HorizontalTailLiftCurveSlopeAtZ = 0.0; // rad^-1 (a_z_h)
    static constexpr double HorizontalTailLiftCurveSlopeAtX = 0.0; // rad^-1 (a_x_h)

    static constexpr double VerticalTailArea = 10.0; // m^2 (S_v)
    static constexpr double VerticalTailSpan = 5.0; // m (b_v)
    static constexpr double VerticalTailChord = 5.0; // m (c_v)
    static constexpr double VerticalTailMeanChord = 5.0; // m (c_bar_v)
    static constexpr double VerticalTailAspectRatio = VerticalTailSpan / VerticalTailChord;
    static constexpr double VerticalTailTaperRatio = 0.5;
    static constexpr double VerticalTailSweepAngle = 0.0; // rad (Lambda_v)
    static constexpr double VerticalTailDihedralAngle = 0.0; // rad (Gamma_v)
    static constexpr double VerticalTailTwistAngle = 0.0; // rad (epsilon_v)
    static constexpr double VerticalTailIncidenceAngle = 0.0; // rad (alpha_0_v)
    static constexpr double VerticalTailZeroLiftAngle = 0.0; // rad (alpha_L0_v)
    static constexpr double VerticalTailLiftCurveSlope = 0.0; // rad^-1 (a_v)
    static constexpr double VerticalTailLiftCurveSlopeAtRoot = 0.0; // rad^-1 (a_0_v)
    static constexpr double VerticalTailLiftCurveSlopeAtTip = 0.0; // rad^-1 (a_1_v)
    static constexpr double VerticalTailLiftCurveSlopeAtMAC = 0.0; // rad^-1 (a_M_v)
    static constexpr double VerticalTailLiftCurveSlopeAtY = 0.0; // rad^-1 (a_y_v)
    static constexpr double VerticalTailLiftCurveSlopeAtZ = 0.0; // rad^-1 (a_z_v)
    static constexpr double VerticalTailLiftCurveSlopeAtX = 0.0; // rad^-1 (a_x_v)
}

#endif /* E310DEA6_9F7E_4DEE_9019_DA65A6CAB980 */
