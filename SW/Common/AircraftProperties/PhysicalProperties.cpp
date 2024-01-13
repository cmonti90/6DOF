#include "PhysicalProperties.h"

namespace Aircraft
{
    double WingArea = 50.0; // m^2 (S)
    double WingSpan = 10.0; // m (b)
    double WingChord = 5.0; // m (c)
    double WingMeanChord = 5.0; // m (c_bar)
    double WingAspectRatio = WingSpan / WingChord;
    double WingTaperRatio = 0.5;
    double WingSweepAngle = 0.0; // rad (Lambda)
    double WingDihedralAngle = 0.0; // rad (Gamma)
    double WingTwistAngle = 0.0; // rad (epsilon)
    double WingIncidenceAngle = 0.0; // rad (alpha_0)
    double WingZeroLiftAngle = 0.0; // rad (alpha_L0)
    double WingLiftCurveSlope = 0.0; // rad^-1 (a)
    double WingLiftCurveSlopeAtRoot = 0.0; // rad^-1 (a_0)
    double WingLiftCurveSlopeAtTip = 0.0; // rad^-1 (a_1)
    double WingLiftCurveSlopeAtMAC = 0.0; // rad^-1 (a_M)
    double WingLiftCurveSlopeAtY = 0.0; // rad^-1 (a_y)
    double WingLiftCurveSlopeAtZ = 0.0; // rad^-1 (a_z)
    double WingLiftCurveSlopeAtX = 0.0; // rad^-1 (a_x)

    double FuselageArea = 10.0; // m^2 (S_f)
    double FuselageLength = 10.0; // m (l_f)
    double FuselageDiameter = 5.0; // m (d_f)
    double FuselageFinenessRatio = FuselageLength / FuselageDiameter;
    double FuselageWettedArea = 0.0; // m^2 (S_wet_f)
    double FuselageZeroLiftAngle = 0.0; // rad (alpha_0_f)
    double FuselageLiftCurveSlope = 0.0; // rad^-1 (a_f)
    double FuselageLiftCurveSlopeAtY = 0.0; // rad^-1 (a_y_f)
    double FuselageLiftCurveSlopeAtZ = 0.0; // rad^-1 (a_z_f)
    double FuselageLiftCurveSlopeAtX = 0.0; // rad^-1 (a_x_f)

    double HorizontalTailArea = 10.0; // m^2 (S_h)
    double HorizontalTailSpan = 5.0; // m (b_h)
    double HorizontalTailChord = 5.0; // m (c_h)
    double HorizontalTailMeanChord = 5.0; // m (c_bar_h)
    double HorizontalTailAspectRatio = HorizontalTailSpan / HorizontalTailChord;
    double HorizontalTailTaperRatio = 0.5;
    double HorizontalTailSweepAngle = 0.0; // rad (Lambda_h)
    double HorizontalTailDihedralAngle = 0.0; // rad (Gamma_h)
    double HorizontalTailTwistAngle = 0.0; // rad (epsilon_h)
    double HorizontalTailIncidenceAngle = 0.0; // rad (alpha_0_h)
    double HorizontalTailZeroLiftAngle = 0.0; // rad (alpha_L0_h)
    double HorizontalTailLiftCurveSlope = 0.0; // rad^-1 (a_h)
    double HorizontalTailLiftCurveSlopeAtRoot = 0.0; // rad^-1 (a_0_h)
    double HorizontalTailLiftCurveSlopeAtTip = 0.0; // rad^-1 (a_1_h)
    double HorizontalTailLiftCurveSlopeAtMAC = 0.0; // rad^-1 (a_M_h)
    double HorizontalTailLiftCurveSlopeAtY = 0.0; // rad^-1 (a_y_h)
    double HorizontalTailLiftCurveSlopeAtZ = 0.0; // rad^-1 (a_z_h)
    double HorizontalTailLiftCurveSlopeAtX = 0.0; // rad^-1 (a_x_h)

    double VerticalTailArea = 10.0; // m^2 (S_v)
    double VerticalTailSpan = 5.0; // m (b_v)
    double VerticalTailChord = 5.0; // m (c_v)
    double VerticalTailMeanChord = 5.0; // m (c_bar_v)
    double VerticalTailAspectRatio = VerticalTailSpan / VerticalTailChord;
    double VerticalTailTaperRatio = 0.5;
    double VerticalTailSweepAngle = 0.0; // rad (Lambda_v)
    double VerticalTailDihedralAngle = 0.0; // rad (Gamma_v)
    double VerticalTailTwistAngle = 0.0; // rad (epsilon_v)
    double VerticalTailIncidenceAngle = 0.0; // rad (alpha_0_v)
    double VerticalTailZeroLiftAngle = 0.0; // rad (alpha_L0_v)
    double VerticalTailLiftCurveSlope = 0.0; // rad^-1 (a_v)
    double VerticalTailLiftCurveSlopeAtRoot = 0.0; // rad^-1 (a_0_v)
    double VerticalTailLiftCurveSlopeAtTip = 0.0; // rad^-1 (a_1_v)
    double VerticalTailLiftCurveSlopeAtMAC = 0.0; // rad^-1 (a_M_v)
    double VerticalTailLiftCurveSlopeAtY = 0.0; // rad^-1 (a_y_v)
    double VerticalTailLiftCurveSlopeAtZ = 0.0; // rad^-1 (a_z_v)
    double VerticalTailLiftCurveSlopeAtX = 0.0; // rad^-1 (a_x_v)
}
