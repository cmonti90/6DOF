
#include "LowRateAutopilotAlgorithm.h"

#include "LowRateDigitalFilterLowPass2.h"
#include "LowRateDigitalFilterComp.h"
#include "LowRateDigitalFilterNotch2.h"
#include "LowRateDigitalFilterLeadLag.h"

#include "AutopilotConstants.h"

#include "Table0D.h"
#include "Table3D.h"

namespace
{
    static float faDataRatio   [2] = {0.0f, 0.0f};
    static float faDataAltitude[2] = {0.0f, 0.0f};
    static float faDataMach    [2] = {0.0f, 0.0f};

    static float faDataKp[8] = {0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f};
    static float faDataKq[8] = {0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f};
    static float faDataKr[8] = {0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f};

    static float faDataKPhi  [8] = {0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f};
    static float faDataKTheta[8] = {0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f};
    static float faDataKPsi  [8] = {0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f};

    static float faDataKAr[8] = {0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f};
    static float faDataKAz[8] = {0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f};
    static float faDataKAy[8] = {0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f};

    static float faDataKAlpha[8] = {0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f};
    static float faDataKBeta [8] = {0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f};

    static float faDataKPR[8] = {0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f};
    static float faDataKYR[8] = {0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f};
    static float faDataKRP[8] = {0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f};
    static float faDataKYP[8] = {0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f};
    static float faDataKRY[8] = {0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f};
    static float faDataKPY[8] = {0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f};

    static Table0D< float > table0DSubRatio   ( faDataRatio, 2 );
    static Table0D< float > table0DSubAltitude( faDataAltitude, 2 );
    static Table0D< float > table0DSubMach    ( faDataMach, 2 );

    static Table3D< float > table3DSubKp( faDataMach, 2, faDataAltitude, 2, faDataRatio, 2, faDataKp, 8 );
    static Table3D< float > table3DSubKq( faDataMach, 2, faDataAltitude, 2, faDataRatio, 2, faDataKq, 8 );
    static Table3D< float > table3DSubKr( faDataMach, 2, faDataAltitude, 2, faDataRatio, 2, faDataKr, 8 );

    static Table3D< float > table3DSubKPhi  ( faDataMach, 2, faDataAltitude, 2, faDataRatio, 2, faDataKPhi, 8 );
    static Table3D< float > table3DSubKTheta( faDataMach, 2, faDataAltitude, 2, faDataRatio, 2, faDataKTheta, 8 );
    static Table3D< float > table3DSubKPsi  ( faDataMach, 2, faDataAltitude, 2, faDataRatio, 2, faDataKPsi, 8 );

    static Table3D< float > table3DSubKAr( faDataMach, 2, faDataAltitude, 2, faDataRatio, 2, faDataKAr, 8 );
    static Table3D< float > table3DSubKAz( faDataMach, 2, faDataAltitude, 2, faDataRatio, 2, faDataKAz, 8 );
    static Table3D< float > table3DSubKAy( faDataMach, 2, faDataAltitude, 2, faDataRatio, 2, faDataKAy, 8 );

    static Table3D< float > table3DSubKAlpha( faDataMach, 2, faDataAltitude, 2, faDataRatio, 2, faDataKAlpha, 8 );
    static Table3D< float > table3DSubKBeta ( faDataMach, 2, faDataAltitude, 2, faDataRatio, 2, faDataKBeta, 8 );

    static Table3D< float > table3DSubIKPR( faDataMach, 2, faDataAltitude, 2, faDataRatio, 2, faDataKPR, 8 );
    static Table3D< float > table3DSubIKYR( faDataMach, 2, faDataAltitude, 2, faDataRatio, 2, faDataKYR, 8 );
    static Table3D< float > table3DSubIKRP( faDataMach, 2, faDataAltitude, 2, faDataRatio, 2, faDataKRP, 8 );
    static Table3D< float > table3DSubIKYP( faDataMach, 2, faDataAltitude, 2, faDataRatio, 2, faDataKYP, 8 );
    static Table3D< float > table3DSubIKRY( faDataMach, 2, faDataAltitude, 2, faDataRatio, 2, faDataKRY, 8 );
    static Table3D< float > table3DSubIKPY( faDataMach, 2, faDataAltitude, 2, faDataRatio, 2, faDataKPY, 8 );

} // namespace

LowRateAutopilotAlgorithm::LowRateAutopilotAlgorithm()
    : azCmd_       ( 0.0f )
    , ayCmd_       ( 0.0f )
    , azCmdLimited_( 0.0f )
    , ayCmdLimited_( 0.0f )

    , u_( 0.0f )
    , v_( 0.0f )
    , w_( 0.0f )

    , aX_( 0.0f )

    , gravityAp_( 0.0f )

    , maxG_              ( 0.0f )
    , cmdErrorLimit_     ( 0.0f )
    , acccelCmdRateLimit_( 0.0f )
    , rollCmdErrorLimit_ ( 0.0f )
    , finStallLimit_     ( 0.0f )

    , gains_()

    , ratio_ ( 0.0f )
    , gAngle_( 0.0f )
    , timeCons_( 0.0f )

    , indexRatio_     ( 0 )
    , indexAltitude_  ( 0 )
    , indexMach_      ( 0 )
    , indexAlphaRatio_( 0 )
    , indexBetaRatio_ ( 0 )
    , indexAngle_     ( 0 )
    , scaleRatio_     ()
    , scaleAltitude_  ()
    , scaleMach_      ()
    , scaleAlphaRatio_()
    , scaleBetaRatio_ ()
    , scaleAngle_     ()

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

    , rollLowPassFilter_( new LowRateDigitalFilterLowPass2() )
    , rollCompFilter_   ( new LowRateDigitalFilterComp() )
    , rollNotchFilter_  ( new LowRateDigitalFilterNotch2() )

    , lateralLowPassFilter_( new LowRateDigitalFilterLowPass2() )
    , lateralCompFilter_   ( new LowRateDigitalFilterComp() )
    , lateralNotch1Filter_ ( new LowRateDigitalFilterNotch2() )
    , lateralNotch2Filter_ ( new LowRateDigitalFilterNotch2() )
{
    std::memset( &rollLowPassFilterParameters_, 0, sizeof( rollLowPassFilterParameters_ ) );
    std::memset( &rollCompFilterParameters_,    0, sizeof( rollCompFilterParameters_ ) );
    std::memset( &rollNotchFilterParameters_,   0, sizeof( rollNotchFilterParameters_ ) );

    std::memset( &lateralLowPassFilterParameters_, 0, sizeof( lateralLowPassFilterParameters_ ) );
    std::memset( &lateralCompFilterParameters_,    0, sizeof( lateralCompFilterParameters_ ) );
    std::memset( &lateralNotch1FilterParameters_,  0, sizeof( lateralNotch1FilterParameters_ ) );
    std::memset( &lateralNotch2FilterParameters_,  0, sizeof( lateralNotch2FilterParameters_ ) );

    // Initialize filters
    rollLowPassFilter_->SetDefaults();
    rollCompFilter_   ->SetDefaults();
    rollNotchFilter_  ->SetDefaults();

    lateralLowPassFilter_->SetDefaults();
    lateralCompFilter_   ->SetDefaults();
    lateralNotch1Filter_ ->SetDefaults();
    lateralNotch2Filter_ ->SetDefaults();
}

LowRateAutopilotAlgorithm::~LowRateAutopilotAlgorithm()
{
}

void LowRateAutopilotAlgorithm::process( const LowRateAutopilotTypes::InData& inData, LowRateAutopilotTypes::OutData& outData )
{
    ProcessNavigationData( inData );

    CalculateGainsAndLimits( inData );

    BuildOutput( outData );
}

void LowRateAutopilotAlgorithm::finalize()
{
}

void LowRateAutopilotAlgorithm::ProcessNavigationData( const LowRateAutopilotTypes::InData& inData )
{
    constexpr float COS45 = std::cos( 45.0f * myMath::Constants::DEG_TO_RAD );
    constexpr float SIN45 = std::sin( 45.0f * myMath::Constants::DEG_TO_RAD );

    const myMath::Vector3f velBody = inData.bodyFromEcef * inData.velEcef;

    // Update the navigation data
    u_ = velBody[0];
    v_ =  COS45 * velBody[1] + SIN45 * velBody[2];
    w_ = -SIN45 * velBody[1] + COS45 * velBody[2];

    aX_ = ( inData.bodyFromEcef * inData.accEcef )[0];

    const myMath::Vector3f gravityBody = inData.bodyFromEcef * inData.gravityEcef;

    gravityAp_[0] = gravityBody[0];
    gravityAp_[1] =  COS45 * gravityBody[1] + SIN45 * gravityBody[2];
    gravityAp_[2] = -SIN45 * gravityBody[1] + COS45 * gravityBody[2];

}

void LowRateAutopilotAlgorithm::CalculateGainsAndLimits( const LowRateAutopilotTypes::InData& inData )
{
    // Calculate flight condition indices
    // TODO:
    // table0DAngle.Reset();

    // table0DRatio   .LookUp( ratio_              , indexRatio_   , scaleRatio_    );
    // table0DAltitude.LookUp( inData.altSeaLevel  , indexAltitude_, scaleAltitude_ );
    // table0DMach    .LookUp( inData.mach         , indexMach_    , scaleMach_     );
    // table0DAngle   .LookUp( std::fabs( gAngle_ ), indexAngle_    , scaleAngle_   );

    // Calculate autopilot gains from interpolation
    LRMTAPGains( inData );

    // Calculate steady state rate command bias
    KssRateCommands( inData );

    // Calculate structural filter frequencies from table interpolation
    LRMTAPFilters();

    // Calculate roll filter coefficients
    rollCompFilter_->SetSampleRate( APConstants::AP_HIGH_RATE );
    rollCompFilter_->SetParameters( rollCompFilterParameters_ );
    rollCompFilter_->CalculateCoefficients();

    rollLowPassFilter_->SetSampleRate( APConstants::AP_HIGH_RATE );
    rollLowPassFilter_->SetParameters( rollLowPassFilterParameters_ );
    rollLowPassFilter_->CalculateCoefficients();

    rollNotchFilter_->SetSampleRate( APConstants::AP_HIGH_RATE );
    rollNotchFilter_->SetParameters( rollNotchFilterParameters_ );
    rollNotchFilter_->CalculateCoefficients();

    // Calculate lateral filter coefficients
    lateralCompFilter_->SetSampleRate( APConstants::AP_HIGH_RATE );
    lateralCompFilter_->SetParameters( lateralCompFilterParameters_ );
    lateralCompFilter_->CalculateCoefficients();

    lateralLowPassFilter_->SetSampleRate( APConstants::AP_HIGH_RATE );
    lateralLowPassFilter_->SetParameters( lateralLowPassFilterParameters_ );
    lateralLowPassFilter_->CalculateCoefficients();

    lateralNotch1Filter_->SetSampleRate( APConstants::AP_HIGH_RATE );
    lateralNotch1Filter_->SetParameters( lateralNotch1FilterParameters_ );
    lateralNotch1Filter_->CalculateCoefficients();

    lateralNotch2Filter_->SetSampleRate( APConstants::AP_HIGH_RATE );
    lateralNotch2Filter_->SetParameters( lateralNotch2FilterParameters_ );
    lateralNotch2Filter_->CalculateCoefficients();


    // Calculate limits from table interpolation
    LRMTAPLimits();

    // TODO:
    // timeCons_ = table3DTimeConstants_.LookUp(
    //                 indexMach_, scaleMach_,
    //                 indexAltitude_, scaleAltitude_,
    //                 indexRatio_, scaleRatio_ );
}


void LowRateAutopilotAlgorithm::KssRateCommands( const LowRateAutopilotTypes::InData& inData )
{
    const float fAxTotal = aX_ * myMath::Constants::GRAVITY_ACCEL + gravityAp_[0];
    const float fAyTotal = ayCmdLimited_ * myMath::Constants::GRAVITY_ACCEL + gravityAp_[1];
    const float fAzTotal = azCmdLimited_ * myMath::Constants::GRAVITY_ACCEL + gravityAp_[2];

    // Compute the trim lateral body rates
    const float fTanAlpha = std::tan( inData.angleOfAttack );
    const float fTanBeta  = std::tan( inData.angleOfSideslip );

    const float fVm = std::sqrt( u_ * u_ + v_ * v_ + w_ * w_ );

    const float Ucmd = fVm / std::sqrt( 1.0f + fTanAlpha * fTanAlpha + fTanBeta * fTanBeta );
    const float Vcmd = Ucmd * fTanBeta;
    const float Wcmd = Ucmd * fTanAlpha;

    const float Usqd = Ucmd * Ucmd;
    const float Vsqd = Vcmd * Vcmd;
    const float Wsqd = Wcmd * Wcmd;

    const float fUVel2 = Ucmd * ( Usqd + Vsqd + Wsqd );

    gains_.KssQ0 = (  Ucmd * Wcmd * fAxTotal + Vcmd * Wcmd * fAyTotal - ( Usqd + Vsqd ) * fAzTotal ) * myMath::Constants::RAD_TO_DEG / fUVel2;
    gains_.KssR0 = ( -Ucmd * Vcmd * fAxTotal - Vcmd * Wcmd * fAyTotal - ( Usqd + Wsqd ) * fAzTotal ) * myMath::Constants::RAD_TO_DEG / fUVel2;
}

void LowRateAutopilotAlgorithm::LRMTAPGains( const LowRateAutopilotTypes::InData& inData )
{
    int idx = 0;

    int idxRatio2;
    int idxAlt2;
    int idxMach2;

    float scaleRatio2[2];
    float scaleAlt2  [2];
    float scaleMach2 [2];

    // Create the subtables. Basiically lookup gains with [Alpha Beta] at the surrounding [Ratio Altitude Mach] breakpoints.
    // Note the values without the underscores are the original indices. The '1' values are used for the +0,+1 increments.
    // The '2' values are the indices modified so we don't go out of bounds.

    for ( int idxRatio1 = indexRatio_; idxRatio1 < indexRatio_ + 2; idxRatio1++ )
    {
        faDataRatio[idxRatio1 - indexRatio_] = gfaDataRatio[idxRatio1];

        if ( idxRatio1 == giLengthDataRatio - 1 )
        {
            scaleRatio2[0] = 0.0f;
            scaleRatio2[1] = 1.0f;
            idxRatio2 = idxRatio1 - 1;
        }
        else
        {
            scaleRatio2[0] = 1.0f;
            scaleRatio2[1] = 0.0f;
            idxRatio2 = idxRatio1;
        }

        // Altitude Loop
        for ( int idxAlt1 = indexAltitude_; idxAlt1 < indexAltitude_ + 2; idxAlt1++ )
        {
            faDataAltitude[idxAlt1 - indexAltitude_] = gfaDataAltitude[idxAlt1];

            if ( idxAlt1 == giLengthDataAltitude - 1 )
            {
                scaleAlt2[0] = 0.0f;
                scaleAlt2[1] = 1.0f;
                idxAlt2 = idxAlt1 - 1;
            }
            else
            {
                scaleAlt2[0] = 1.0f;
                scaleAlt2[1] = 0.0f;
                idxAlt2 = idxAlt1;
            }

            // Mach Loop
            for ( int idxMach1 = indexMach_; idxMach1 < indexMach_ + 2; idxMach1++ )
            {
                faDataMach[idxMach1 - indexMach_] = gfaDataMach[idxMach1];

                if ( idxMach1 == giLengthDataMach - 1 )
                {
                    scaleMach2[0] = 0.0f;
                    scaleMach2[1] = 1.0f;
                    idxMach2 = idxMach1 - 1;
                }
                else
                {
                    scaleMach2[0] = 1.0f;
                    scaleMach2[1] = 0.0f;
                    idxMach2 = idxMach1;
                }

                const float maxAlpha = table3DKMaxAlpha.LookUp( idxMach2, scaleMach2, idxAlt2, scaleAlt2, idxRatio2, scaleRatio2 );

                const float alphaRatio = inData.angleOfAttack   / maxAlpha;
                const float betaRatio  = inData.angleOfSideslip / maxAlpha;

                table0DAlphaRatio.LookUp( alphaRatio, indexAlphaRatio_, scaleAlphaRatio_ );
                table0DBetaRatio .LookUp( betaRatio, indexBetaRatio_, scaleBetaRatio_  );

                faDataKp    [idx] = table5DKp    .LookUp( indexBetaRatio_, scaleBetaRatio_, indexAlphaRatio_, scaleAlphaRatio_, idxMach2, scaleMach2, idxAlt2, scaleAlt2, idxRatio2, scaleRatio2 );
                faDataKq    [idx] = table5DKq    .LookUp( indexBetaRatio_, scaleBetaRatio_, indexAlphaRatio_, scaleAlphaRatio_, idxMach2, scaleMach2, idxAlt2, scaleAlt2, idxRatio2, scaleRatio2 );
                faDataKr    [idx] = table5DKr    .LookUp( indexBetaRatio_, scaleBetaRatio_, indexAlphaRatio_, scaleAlphaRatio_, idxMach2, scaleMach2, idxAlt2, scaleAlt2, idxRatio2, scaleRatio2 );
                faDataKPhi  [idx] = table5DKPhi  .LookUp( indexBetaRatio_, scaleBetaRatio_, indexAlphaRatio_, scaleAlphaRatio_, idxMach2, scaleMach2, idxAlt2, scaleAlt2, idxRatio2, scaleRatio2 );
                faDataKTheta[idx] = table5DKTheta.LookUp( indexBetaRatio_, scaleBetaRatio_, indexAlphaRatio_, scaleAlphaRatio_, idxMach2, scaleMach2, idxAlt2, scaleAlt2, idxRatio2, scaleRatio2 );
                faDataKPsi  [idx] = table5DKPsi  .LookUp( indexBetaRatio_, scaleBetaRatio_, indexAlphaRatio_, scaleAlphaRatio_, idxMach2, scaleMach2, idxAlt2, scaleAlt2, idxRatio2, scaleRatio2 );
                faDataKAr   [idx] = table5DAr    .LookUp( indexBetaRatio_, scaleBetaRatio_, indexAlphaRatio_, scaleAlphaRatio_, idxMach2, scaleMach2, idxAlt2, scaleAlt2, idxRatio2, scaleRatio2 );
                faDataKAz   [idx] = table5DAz    .LookUp( indexBetaRatio_, scaleBetaRatio_, indexAlphaRatio_, scaleAlphaRatio_, idxMach2, scaleMach2, idxAlt2, scaleAlt2, idxRatio2, scaleRatio2 );
                faDataKAy   [idx] = table5DAy    .LookUp( indexBetaRatio_, scaleBetaRatio_, indexAlphaRatio_, scaleAlphaRatio_, idxMach2, scaleMach2, idxAlt2, scaleAlt2, idxRatio2, scaleRatio2 );
                faDataKAlpha[idx] = table5DKAlpha.LookUp( indexBetaRatio_, scaleBetaRatio_, indexAlphaRatio_, scaleAlphaRatio_, idxMach2, scaleMach2, idxAlt2, scaleAlt2, idxRatio2, scaleRatio2 );
                faDataKBeta [idx] = table5DKBeta .LookUp( indexBetaRatio_, scaleBetaRatio_, indexAlphaRatio_, scaleAlphaRatio_, idxMach2, scaleMach2, idxAlt2, scaleAlt2, idxRatio2, scaleRatio2 );
                faDataKPR   [idx] = table5DKPR   .LookUp( indexBetaRatio_, scaleBetaRatio_, indexAlphaRatio_, scaleAlphaRatio_, idxMach2, scaleMach2, idxAlt2, scaleAlt2, idxRatio2, scaleRatio2 );
                faDataKYR   [idx] = table5DKYR   .LookUp( indexBetaRatio_, scaleBetaRatio_, indexAlphaRatio_, scaleAlphaRatio_, idxMach2, scaleMach2, idxAlt2, scaleAlt2, idxRatio2, scaleRatio2 );
                faDataKRP   [idx] = table5DKRP   .LookUp( indexBetaRatio_, scaleBetaRatio_, indexAlphaRatio_, scaleAlphaRatio_, idxMach2, scaleMach2, idxAlt2, scaleAlt2, idxRatio2, scaleRatio2 );
                faDataKYP   [idx] = table5DKYP   .LookUp( indexBetaRatio_, scaleBetaRatio_, indexAlphaRatio_, scaleAlphaRatio_, idxMach2, scaleMach2, idxAlt2, scaleAlt2, idxRatio2, scaleRatio2 );
                faDataKRY   [idx] = table5DKRY   .LookUp( indexBetaRatio_, scaleBetaRatio_, indexAlphaRatio_, scaleAlphaRatio_, idxMach2, scaleMach2, idxAlt2, scaleAlt2, idxRatio2, scaleRatio2 );
                faDataKPY   [idx] = table5DKPY   .LookUp( indexBetaRatio_, scaleBetaRatio_, indexAlphaRatio_, scaleAlphaRatio_, idxMach2, scaleMach2, idxAlt2, scaleAlt2, idxRatio2, scaleRatio2 );

                idx++;
            }
        }
    }

    // Sublookup. Look up [Ratio Altitutde Mach] with the newly created tables
    table0DSubRatio   .LookUp( ratio_,             idxRatio2, scaleRatio2 );
    table0DSubAltitude.LookUp( inData.altSeaLevel, idxAlt2,   scaleAlt2   );
    table0DSubMach    .LookUp( inData.mach,        idxMach2,  scaleMach2  );

    gains_.Kp     = table3DSubKp    .LookUp( idxMach2, scaleMach2, idxAlt2, scaleAlt2, idxRatio2, scaleRatio2 );
    gains_.Kq     = table3DSubKq    .LookUp( idxMach2, scaleMach2, idxAlt2, scaleAlt2, idxRatio2, scaleRatio2 );
    gains_.Kr     = table3DSubKr    .LookUp( idxMach2, scaleMach2, idxAlt2, scaleAlt2, idxRatio2, scaleRatio2 );
    gains_.KPhi   = table3DSubKPhi  .LookUp( idxMach2, scaleMach2, idxAlt2, scaleAlt2, idxRatio2, scaleRatio2 );
    gains_.KTheta = table3DSubKTheta.LookUp( idxMach2, scaleMach2, idxAlt2, scaleAlt2, idxRatio2, scaleRatio2 );
    gains_.KPsi   = table3DSubKPsi  .LookUp( idxMach2, scaleMach2, idxAlt2, scaleAlt2, idxRatio2, scaleRatio2 );
    gains_.KAr    = table3DSubKAr   .LookUp( idxMach2, scaleMach2, idxAlt2, scaleAlt2, idxRatio2, scaleRatio2 );
    gains_.KAz    = table3DSubKAz   .LookUp( idxMach2, scaleMach2, idxAlt2, scaleAlt2, idxRatio2, scaleRatio2 );
    gains_.KAy    = table3DSubKAy   .LookUp( idxMach2, scaleMach2, idxAlt2, scaleAlt2, idxRatio2, scaleRatio2 );
    gains_.KAlpha = table3DSubKAlpha.LookUp( idxMach2, scaleMach2, idxAlt2, scaleAlt2, idxRatio2, scaleRatio2 );
    gains_.KBeta  = table3DSubKBeta .LookUp( idxMach2, scaleMach2, idxAlt2, scaleAlt2, idxRatio2, scaleRatio2 );
    gains_.IKPR   = table3DSubIKPR  .LookUp( idxMach2, scaleMach2, idxAlt2, scaleAlt2, idxRatio2, scaleRatio2 );
    gains_.IKYR   = table3DSubIKYR  .LookUp( idxMach2, scaleMach2, idxAlt2, scaleAlt2, idxRatio2, scaleRatio2 );
    gains_.IKRP   = table3DSubIKRP  .LookUp( idxMach2, scaleMach2, idxAlt2, scaleAlt2, idxRatio2, scaleRatio2 );
    gains_.IKYP   = table3DSubIKYP  .LookUp( idxMach2, scaleMach2, idxAlt2, scaleAlt2, idxRatio2, scaleRatio2 );
    gains_.IKRY   = table3DSubIKRY  .LookUp( idxMach2, scaleMach2, idxAlt2, scaleAlt2, idxRatio2, scaleRatio2 );
    gains_.IKPY   = table3DSubIKPY  .LookUp( idxMach2, scaleMach2, idxAlt2, scaleAlt2, idxRatio2, scaleRatio2 );

    // For conventional 9x5 scheduling of gains across LHP of alpha/beta
    if ( inData.angleOfSideslip < 0.0f )
    {
        gains_.KRP = -gains_.IKRP;
        gains_.KPR = -gains_.IKPR;
        gains_.KPY = -gains_.IKPY;
        gains_.KYP = -gains_.IKYP;

        gains_.KAlpha = -gains_.KAlpha;
    }

    // Invert Kcd matrix

    gains_.IKRR = 1.0f;
    gains_.IKPP = 1.0f;
    gains_.IKYY = 1.0f;

    const float scale = gains_.IKRR * gains_.IKPP * gains_.IKYY - gains_.IKRR * gains_.IKYP * gains_.IKPY
                        + gains_.IKPR * gains_.IKYP * gains_.IKRY - gains_.IKPR * gains_.IKRP * gains_.IKYY
                        + gains_.IKYR * gains_.IKRP * gains_.IKPY - gains_.IKYR * gains_.IKPP * gains_.IKRY;

    gains_.KRR = (  gains_.IKPP * gains_.IKYY - gains_.IKPY * gains_.IKYP ) / scale;
    gains_.KRP = ( -gains_.IKRP * gains_.IKYY + gains_.IKRY * gains_.IKYP ) / scale;
    gains_.KRY = (  gains_.IKRP * gains_.IKPY - gains_.IKRY * gains_.IKPP ) / scale;

    gains_.KPR = ( -gains_.IKPR * gains_.IKYY + gains_.IKPY * gains_.IKYR ) / scale;
    gains_.KPP = (  gains_.IKRR * gains_.IKYY - gains_.IKRY * gains_.IKYR ) / scale;
    gains_.KPY = ( -gains_.IKRR * gains_.IKPY + gains_.IKRY * gains_.IKPR ) / scale;

    gains_.KYR = (  gains_.IKPR * gains_.IKYP - gains_.IKPP * gains_.IKYR ) / scale;
    gains_.KYY = (  gains_.IKRR * gains_.IKPP - gains_.IKRP * gains_.IKPR ) / scale;
    gains_.KYP = ( -gains_.IKRR * gains_.IKYP + gains_.IKRP * gains_.IKYR ) / scale;
}

void LowRateAutopilotAlgorithm::LRMTAPLimits()
{
    maxG_ = table4DMaxG.LookUp( indexAngle_, scaleAngle_,
                                indexMach_, scaleMach_,
                                indexAltitude_, scaleAltitude_,
                                indexRatio_, scaleRatio_ );

    cmdErrorLimit_ = table3DCmdErrorLimits.LookUp( indexMach_, scaleMach_,
                     indexAltitude_, scaleAltitude_,
                     indexRatio_, scaleRatio_ );

    acccelCmdRateLimit_ = table3DAccelCmdRateLimits.LookUp( indexMach_, scaleMach_,
                          indexAltitude_, scaleAltitude_,
                          indexRatio_, scaleRatio_ );

    rollCmdErrorLimit_ = table3DRollCmdErrorLimits.LookUp( indexMach_, scaleMach_,
                         indexAltitude_, scaleAltitude_,
                         indexRatio_, scaleRatio_ );

    finStallLimit_ = table3DFinStallLimits.LookUp( indexMach_, scaleMach_,
                     indexAltitude_, scaleAltitude_,
                     indexRatio_, scaleRatio_ );
}

void LowRateAutopilotAlgorithm::LRMTAPFilters()
{
    rollLowPassFilterParameters_[0]   = table3DRollLPFreq        .LookUp( indexMach_, scaleMach_, indexAltitude_, scaleAltitude_, indexRatio_, scaleRatio_ );
    rollLowPassFilterParameters_[1]   = table3DRollLPZeta        .LookUp( indexMach_, scaleMach_, indexAltitude_, scaleAltitude_, indexRatio_, scaleRatio_ );

    rollCompFilterParameters_[0]      = table3DRollLeadFreq      .LookUp( indexMach_, scaleMach_, indexAltitude_, scaleAltitude_, indexRatio_, scaleRatio_ );
    rollCompFilterParameters_[1]      = table3DRollLagFreq       .LookUp( indexMach_, scaleMach_, indexAltitude_, scaleAltitude_, indexRatio_, scaleRatio_ );
    rollCompFilterParameters_[2]      = table3DRollLagZeta       .LookUp( indexMach_, scaleMach_, indexAltitude_, scaleAltitude_, indexRatio_, scaleRatio_ );

    rollNotchFilterParameters_[0]      = table3DRollNotFreq      .LookUp( indexMach_, scaleMach_, indexAltitude_, scaleAltitude_, indexRatio_, scaleRatio_ );
    rollNotchFilterParameters_[1]      = table3DRollNotRipple    .LookUp( indexMach_, scaleMach_, indexAltitude_, scaleAltitude_, indexRatio_, scaleRatio_ );
    rollNotchFilterParameters_[2]      = table3DRollNotDepth     .LookUp( indexMach_, scaleMach_, indexAltitude_, scaleAltitude_, indexRatio_, scaleRatio_ );
    rollNotchFilterParameters_[3]      = table3DRollNotWidth     .LookUp( indexMach_, scaleMach_, indexAltitude_, scaleAltitude_, indexRatio_, scaleRatio_ );

    lateralLowPassFilterParameters_[0] = table3DLateralLPFreq    .LookUp( indexMach_, scaleMach_, indexAltitude_, scaleAltitude_, indexRatio_, scaleRatio_ );
    lateralLowPassFilterParameters_[1] = table3DLateralLPZeta    .LookUp( indexMach_, scaleMach_, indexAltitude_, scaleAltitude_, indexRatio_, scaleRatio_ );

    lateralCompFilterParameters_[0]    = table3DLateralLeadFreq  .LookUp( indexMach_, scaleMach_, indexAltitude_, scaleAltitude_, indexRatio_, scaleRatio_ );
    lateralCompFilterParameters_[1]    = table3DLateralLagFreq   .LookUp( indexMach_, scaleMach_, indexAltitude_, scaleAltitude_, indexRatio_, scaleRatio_ );
    lateralCompFilterParameters_[2]    = table3DLateralLagZeta   .LookUp( indexMach_, scaleMach_, indexAltitude_, scaleAltitude_, indexRatio_, scaleRatio_ );

    lateralNotch1FilterParameters_[0]  = table3DLateralNot1Freq  .LookUp( indexMach_, scaleMach_, indexAltitude_, scaleAltitude_, indexRatio_, scaleRatio_ );
    lateralNotch1FilterParameters_[1]  = table3DLateralNot1Ripple.LookUp( indexMach_, scaleMach_, indexAltitude_, scaleAltitude_, indexRatio_, scaleRatio_ );
    lateralNotch1FilterParameters_[2]  = table3DLateralNot1Depth .LookUp( indexMach_, scaleMach_, indexAltitude_, scaleAltitude_, indexRatio_, scaleRatio_ );
    lateralNotch1FilterParameters_[3]  = table3DLateralNot1Width .LookUp( indexMach_, scaleMach_, indexAltitude_, scaleAltitude_, indexRatio_, scaleRatio_ );

    lateralNotch2FilterParameters_[0]  = table3DLateralNot2Freq  .LookUp( indexMach_, scaleMach_, indexAltitude_, scaleAltitude_, indexRatio_, scaleRatio_ );
    lateralNotch2FilterParameters_[1]  = table3DLateralNot2Ripple.LookUp( indexMach_, scaleMach_, indexAltitude_, scaleAltitude_, indexRatio_, scaleRatio_ );
    lateralNotch2FilterParameters_[2]  = table3DLateralNot2Depth .LookUp( indexMach_, scaleMach_, indexAltitude_, scaleAltitude_, indexRatio_, scaleRatio_ );
    lateralNotch2FilterParameters_[3]  = table3DLateralNot2Width .LookUp( indexMach_, scaleMach_, indexAltitude_, scaleAltitude_, indexRatio_, scaleRatio_ );

    rollLowPassFreq_         = rollLowPassFilterParameters_[0];
    rollLowPassDampingRatio_ = rollLowPassFilterParameters_[1];

    rollCompLeadFreq_        = rollCompFilterParameters_[0];
    rollCompLagFreq_         = rollCompFilterParameters_[1];
    rollCompLagDampingRatio_ = rollCompFilterParameters_[2];

    rollNotchFreq_           = rollNotchFilterParameters_[0];
    rollNotchRipple_         = rollNotchFilterParameters_[1];
    rollNotchDepth_          = rollNotchFilterParameters_[2];
    rollNotchWidth_          = rollNotchFilterParameters_[3];

    lateralLowPassFreq_         = lateralLowPassFilterParameters_[0];
    lateralLowPassDampingRatio_ = lateralLowPassFilterParameters_[1];

    lateralCompLeadFreq_        = lateralCompFilterParameters_[0];
    lateralCompLagFreq_         = lateralCompFilterParameters_[1];
    lateralCompLagDampingRatio_ = lateralCompFilterParameters_[2];

    lateralNotch1Freq_          = lateralNotch1FilterParameters_[0];
    lateralNotch1Ripple_        = lateralNotch1FilterParameters_[1];
    lateralNotch1Depth_         = lateralNotch1FilterParameters_[2];
    lateralNotch1Width_         = lateralNotch1FilterParameters_[3];

    lateralNotch2Freq_          = lateralNotch2FilterParameters_[0];
    lateralNotch2Ripple_        = lateralNotch2FilterParameters_[1];
    lateralNotch2Depth_         = lateralNotch2FilterParameters_[2];
    lateralNotch2Width_         = lateralNotch2FilterParameters_[3];

}

void LowRateAutopilotAlgorithm::BuildOutput( LowRateAutopilotTypes::OutData& outData )
{
    // TODO
}

float LowRateAutopilotAlgorithm::Orientation( const float angle ) const
{
    // Normalize angle between [-180, 180) degrees

    float angleOut = angle - static_cast< float >( static_cast< int >( angle / 360.0f ) ) * 360.0f;

    if ( angleOut >= 180.0f )
    {
        angleOut -= 360.0f;
    }
    else if ( angleOut < -180.0f )
    {
        angleOut += 360.0f;
    }

    return angleOut;
}