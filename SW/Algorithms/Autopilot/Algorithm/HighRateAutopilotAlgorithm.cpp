
#include "HighRateAutopilotAlgorithm.h"

#include "AutopilotConstants.h"

#include "FilterP.h"
#include "FilterQR.h"
#include "FilterRollDC.h"

namespace
{
    constexpr float COS45 = std::cos( 45.0f * myMath::Constants::DEG_TO_RAD );
    constexpr float SIN45 = std::sin( 45.0f * myMath::Constants::DEG_TO_RAD );


    // This adaptive glimits algorithm adjusts the glimits based upon
    // 1. the proximity of the control effort near design limits, and
    // 2. the persustence of control loop error
    // This has been found useful when contorl authority is marginal and can be eroded by plant variations

    constexpr float AGA_FIN_LO_LIMIT      = 0.90f;          // [-]    Fraction of fin SW limit, ACA counter steps down
    constexpr float AGA_FIN_HI_LIMIT      = 0.95f;          // [-]    Fraction of fin SW limit, ACA counter steps up
    constexpr float AGA_ROLL_ERR_LIMIT    = 5.0f;           // [rad] Roll error limit for ACA engagement
    constexpr float AGA_ACCEL_ERROR_LIMIT = 0.1f;           // [-] Acceleration error as a fraction of glimit for ACA engagement
    constexpr float AGA_SF_LO_LIMIT       = 0.1f;           // [-] Lower limit of glimit scale factor
    constexpr float AGA_SF_HI_LIMIT       = 1.0f;           // [-] Upper limit of glimit scale factor
    constexpr float AGA_COUNT_DOWN_INC    = 1.0f / 300.0f;  // [-] Resolution of glimit scale factor counting down
    constexpr float AGA_COUNT_UP_INC      = 1.0f / 4000.0f; // [-] Resolution of glimit scale factor counting up

    // Tactical ACRL schedule implementation: Throttle back during midcourse, relax to ACRL table values (and maybe more) with tautogo
    constexpr float ACRLSDL_TAUTOGO_START = 20.0f;
    constexpr float ACRLSDL_TAUTOGO_STOP  = 3.0f;
    constexpr float ACRLSDL_EXP_SLOPE     = 0.2f;
    constexpr float ACRLSDL_MDCRS_SF      = 0.6f;
    constexpr float ACRLSDL_TERM_SF       = 0.8f;

    // Roll and pull
    constexpr float RNP_FILTER_ALPHA                 = 0.005f; // [-]
    constexpr float RNP_MAXG_GANGLE                  = 45.0f;  // [deg]
    constexpr float RNP_MINMAX_MAXGRATIO_THRESHOLD   = 0.875f; // [-]
    constexpr float RNP_GCMD_RATIO_ON_THRESHOLD      = 1.20f;  // [-]
    constexpr float RNP_GCMD_RATIO_OFF_THRESHOLD     = 0.2f;   // [-]
    constexpr float RNP_TAUTOGO_LOCKOUT              = 3.0f;   // [-]
    constexpr float RNP_ROLLERROR_RATIO_ON_THRESHOLD = 0.25f;  // [-]
    constexpr float RNP_MAXP_ON_THRESHOLD            = 50.0f;  // [deg/s]
    constexpr float RNP_GANGLERATE_ON_THRESHOLD      = 200.0f; // [deg/s]
    constexpr float RNP_BIAS_LIMIT_RCEL_RATIO        = 1.0f;   // [-]
    constexpr float RNP_KD_GAIN_FACTOR               = 0.5f;   // [-]

} // namespace

HighRateAutopilotAlgorithm::HighRateAutopilotAlgorithm()
    : u_( 0.0f )
    , v_( 0.0f )
    , w_( 0.0f )

    , aX_( 0.0f )
    , aY_( 0.0f )
    , aZ_( 0.0f )

    , gravityAp_{ 0.0f, 0.0f, 0.0f }

    , maxG_             ( 0.0f )
    , accelCmdRateLimit_( 0.0f )
    , cmdErrorLimit_    ( 0.0f )
    , rollCmdErrorLimit_( 0.0f )
    , finStallLimit_    ( 0.0f )

    , apGains_          ()

    , integratedRollRate_( 0.0f )
    , integratedRollRateGuidance_( 0.0f )
    , cmdRoll_           ( 0.0f )

    , adaptGLimits_( false )

    , maxGSF_  ( 0.0f )
    , ctrlPref_( 0 )

    , navVel_{ 0.0f, 0.0f, 0.0f }

    , p_( 0.0f )
    , q_( 0.0f )
    , r_( 0.0f )

    , pFiltered_( 0.0f )
    , qFiltered_( 0.0f )
    , rFiltered_( 0.0f )

    , deltaRoll_   ( 0.0f )
    , cosDeltaRoll_( std::cos( deltaRoll_ ) )
    , sinDeltaRoll_( std::sin( deltaRoll_ ) )

    , rateLimitedRollCmd_( 0.0f )

    , ayCmd_           ( 0.0f )
    , azCmd_           ( 0.0f )
    , cmdMagGs_        ( 0.0f )
    , ayCmdLimited_    ( 0.0f )
    , azCmdLimited_    ( 0.0f )
    , ayCmdRateLimited_( 0.0f )
    , azCmdRateLimited_( 0.0f )

    , ayCmdRotated_( 0.0f )
    , azCmdRotated_( 0.0f )

    , rollError_       ( 0.0f )
    , rollErrorLimited_( 0.0f )

    , azError_         ( 0.0f )
    , ayError_         ( 0.0f )
    , cmdErrorMag_     ( 0.0f )
    , azErrorLimited_  ( 0.0f )
    , ayErrorLimited_  ( 0.0f )

    , uRate_   ( 0.0f )
    , vRate_   ( 0.0f )
    , wRate_   ( 0.0f )
    , alphaDot_( 0.0f )
    , betaDot_ ( 0.0f )

    , rollDecoupling_        ( 0.0f )
    , rollDecouplingFiltered_( 0.0f )

    , pCmd_( 0.0f )
    , qCmd_( 0.0f )
    , rCmd_( 0.0f )

    , pCmdFiltered_( 0.0f )
    , qCmdFiltered_( 0.0f )
    , rCmdFiltered_( 0.0f )

    , integratorPInput_( 0.0f )
    , integratorQInput_( 0.0f )
    , integratorRInput_( 0.0f )

    , integratorP_( 0.0f )
    , integratorQ_( 0.0f )
    , integratorR_( 0.0f )

    , rollDeflCmd_ ( 0.0f )
    , pitchDeflCmd_( 0.0f )
    , yawDeflCmd_  ( 0.0f )

    , rollDeflCmdDecoupled_ ( 0.0f )
    , pitchDeflCmdDecoupled_( 0.0f )
    , yawDeflCmdDecoupled_  ( 0.0f )

    , maxDefl_( 0.0f )

    , antiWindup_( false )

    , rollDeflCmdDecLimited_ ( 0.0f )
    , pitchDeflCmdDecLimited_( 0.0f )
    , yawDeflCmdDecLimited_  ( 0.0f )

    , rollDeflCmdLtdPreMSFR_ ( 0.0f )
    , pitchDeflCmdLtdPreMSFR_( 0.0f )
    , yawDeflCmdLtdPreMSFR_  ( 0.0f )

    , fin1Cmd_( 0.0f )
    , fin2Cmd_( 0.0f )
    , fin3Cmd_( 0.0f )
    , fin4Cmd_( 0.0f )

    , scsDelta1Cmd_( 0.0f )
    , scsDelta2Cmd_( 0.0f )
    , scsDelta3Cmd_( 0.0f )
    , scsDelta4Cmd_( 0.0f )

    , filterP_     ( new FilterP() )
    , filterQ_     ( new FilterQR() )
    , filterR_     ( new FilterQR() )
    , filterRollDC_( new FilterRollDC() )
    , filterQCmd_  ( new FilterQR() )
    , filterRCmd_  ( new FilterQR() )

    , firstPass_( true )

    , sysIdEnable_       ( false )
    , sysIdMag_          ( 1.0f )
    , sysIdDuration      ( 10.0f )
    , sysIdChirpDuration_( 0.0f )
    , sysIdDelay_        ( 1.0f )
    , sysIdFreq_         ( 5.0f )
    , sysIdChannel_      ( 0.0f )
    , sysIdChirp_        ( 0.0f )
    , sysIdFreqStart_    ( 0.0f )
    , sysIdFreqEnd_      ( 0.0f )
{
}


HighRateAutopilotAlgorithm::~HighRateAutopilotAlgorithm()
{
}


void HighRateAutopilotAlgorithm::process( const HighRateAutopilotTypes::InData& inData, HighRateAutopilotTypes::OutData& outData )
{
    // Set apGains
    apGains_ = inData.apGains;

    const myMath::Vector3f velAp = inData.bodyFromEcef * inData.velEcef;

    u_ = velAp[0];
    v_ =  COS45 * velAp[1] + SIN45 * velAp[2];
    w_ = -SIN45 * velAp[1] + COS45 * velAp[2];

    const myMath::Vector3f gravityBody = inData.bodyFromEcef * inData.gravityEcef;

    gravityAp_[0] = gravityBody[0];
    gravityAp_[1] =  COS45 * gravityBody[1] + SIN45 * gravityBody[2];
    gravityAp_[2] = -SIN45 * gravityBody[1] + COS45 * gravityBody[2];

    maxG_              = inData.maxG;
    accelCmdRateLimit_ = inData.accelCmdRateLimit;
    cmdErrorLimit_     = inData.cmdErrorLimit;
    rollCmdErrorLimit_ = inData.rollCmdErrorLimit;
    finStallLimit_     = inData.finStallLimit;

    integratedRollRateGuidance_ = inData.integratedRollRate;
    cmdRoll_ = inData.cmdRoll;

    // Set filter coefficients
    filterP_->SetCoefficients( inData.rollLowPassFilterNum,
                               inData.rollLowPassFilterDen,
                               inData.rollNotchFilterNum,
                               inData.rollNotchFilterDen,
                               inData.rollCompFilterNum,
                               inData.rollCompFilterDen );

    filterQ_->SetCoefficients( inData.lateralLowPassFilterNum,
                               inData.lateralLowPassFilterDen,
                               inData.lateralNotchFilter1Num,
                               inData.lateralNotchFilter1Den,
                               inData.lateralNotchFilter2Num,
                               inData.lateralNotchFilter2Den,
                               inData.lateralCompFilterNum,
                               inData.lateralCompFilterDen );

    filterR_->SetCoefficients( inData.lateralLowPassFilterNum,
                               inData.lateralLowPassFilterDen,
                               inData.lateralNotchFilter1Num,
                               inData.lateralNotchFilter1Den,
                               inData.lateralNotchFilter2Num,
                               inData.lateralNotchFilter2Den,
                               inData.lateralCompFilterNum,
                               inData.lateralCompFilterDen );

    filterQCmd_->SetCoefficients( inData.lateralLowPassFilterNum,
                                  inData.lateralLowPassFilterDen,
                                  inData.lateralNotchFilter1Num,
                                  inData.lateralNotchFilter1Den,
                                  inData.lateralNotchFilter2Num,
                                  inData.lateralNotchFilter2Den,
                                  inData.lateralCompFilterNum,
                                  inData.lateralCompFilterDen );

    filterRCmd_->SetCoefficients( inData.lateralLowPassFilterNum,
                                  inData.lateralLowPassFilterDen,
                                  inData.lateralNotchFilter1Num,
                                  inData.lateralNotchFilter1Den,
                                  inData.lateralNotchFilter2Num,
                                  inData.lateralNotchFilter2Den,
                                  inData.lateralCompFilterNum,
                                  inData.lateralCompFilterDen );

    filterRollDC_->SetCoefficients( inData.lateralNotchFilter1Num,
                                    inData.lateralNotchFilter1Den,
                                    inData.lateralNotchFilter2Num,
                                    inData.lateralNotchFilter2Den );


    ProcessImuData( inData );

    ProcessGuidanceCommands( inData );

    ExecuteControlLaw( inData );

    BuildOutput( outData );
}


void HighRateAutopilotAlgorithm::finalize()
{
}


void HighRateAutopilotAlgorithm::ExecuteControlLaw(const HighRateAutopilotTypes::InData& inData )
{
    // Filter measured body rates
    pFiltered_ = filterP_->Update( p_ );
    qFiltered_ = filterQ_->Update( q_ );
    rFiltered_ = filterR_->Update( r_ );

    // Rotate acceleration command through delta roll angle since last guidance update
    deltaRoll_ = integratedRollRate_  - integratedRollRateGuidance_;
    cosDeltaRoll_ = std::cos( deltaRoll_ );
    sinDeltaRoll_ = std::sin( deltaRoll_ );

    // Integrate roll body rate
    integratedRollRate_ += pFiltered_ * APConstants::AP_HIGH_RATE_DELTA_T;

    ayCmdRotated_ =  -sinDeltaRoll_ * ayCmdRateLimited_ + cosDeltaRoll_ * azCmdRateLimited_;
    azCmdRotated_ =   cosDeltaRoll_ * ayCmdRateLimited_ + sinDeltaRoll_ * azCmdRateLimited_;

    // Compute roll, acceleration errors, and angle errors
    cmdRollRateLimited_ += std::max( -APConstants::ROLL_CMD_RATE_LIMIT * APConstants::AP_HIGH_RATE_DELTA_T, std::min( APConstants::ROLL_CMD_RATE_LIMIT * APConstants::AP_HIGH_RATE_DELTA_T, cmdRoll_ - cmdRollRateLimited_ ) );
    rollError_ = -cmdRollRateLimited_ + integratedRollRate_;

    ayError_ = -ayCmdRotated_ + aY_;
    azError_ =  azCmdRotated_ - aZ_;

    // Limit acceleration and angle errors
    // Acceleration error limiting
    cmdErrorMag_ = std::sqrt( ayError_ * ayError_ + azError_ * azError_ );

    if ( cmdErrorMag_ > cmdErrorLimit_ )
    {
        const float errorRatio = cmdErrorLimit_ / cmdErrorMag_;

        ayErrorLimited_ = ayError_ * errorRatio;
        azErrorLimited_ = azError_ * errorRatio;
    }
    else
    {
        ayErrorLimited_ = ayError_;
        azErrorLimited_ = azError_;
    }

    // Angle error limiting
    rollErrorLimited_ = std::max( -rollCmdErrorLimit_, std::min( rollCmdErrorLimit_, rollError_ ) );

    // Compute roll decoupling
    uRate_ = v_ * r_ - w_ * q_ + aX_ * myMath::Constants::GRAVITY_ACCEL + gravityAp_[0];
    vRate_ = w_ * p_ - u_ * r_ + aY_ * myMath::Constants::GRAVITY_ACCEL + gravityAp_[1];
    wRate_ = u_ * q_ - v_ * p_ + aZ_ * myMath::Constants::GRAVITY_ACCEL + gravityAp_[2];

    alphaDot_ = ( u_ * wRate_ - w_ * uRate_ ) / ( u_ * u_ + w_ * w_ );
    betaDot_  = ( u_ * vRate_ - v_ * uRate_ ) / ( u_ * u_ + v_ * v_ );

    rollDecoupling_ = apGains_.KBeta * betaDot_ + apGains_.KAlpha * alphaDot_;

    // Filter roll decoupling
    rollDecouplingFiltered_ = filterRollDC_->Update( rollDecoupling_ );

    // Compute rate commands
    pCmd_ = apGains_.KAr * rollErrorLimited_;
    qCmd_ = apGains_.KAz * azErrorLimited_ - apGains_.KTheta * apGains_.KssQ0;
    rCmd_ = apGains_.KAy * ayErrorLimited_ - apGains_.KPsi   * apGains_.KssR0;

    // Filter rate commands
    if ( sysIdEnable_ )
    {
        pCmdFiltered_ = 0.0;
        qCmdFiltered_ = 0.0;
        rCmdFiltered_ = 0.0;
    }
    else
    {
        pCmdFiltered_ = pCmd_;
        qCmdFiltered_ = filterQCmd_->Update( qCmd_ );
        rCmdFiltered_ = filterRCmd_->Update( rCmd_ );
    }

    integratorPInput_ = pCmdFiltered_ + apGains_.KPhi   * pFiltered_ - rollDecouplingFiltered_;
    integratorQInput_ = qCmdFiltered_ + apGains_.KTheta * qFiltered_;
    integratorRInput_ = rCmdFiltered_ + apGains_.KPsi   * rFiltered_;

    // Update integrator
    integratorP_ += integratorPInput_ * APConstants::AP_HIGH_RATE_DELTA_T;
    integratorQ_ += integratorQInput_ * APConstants::AP_HIGH_RATE_DELTA_T;
    integratorR_ += integratorRInput_ * APConstants::AP_HIGH_RATE_DELTA_T;

    // Compute control surface commands
    rollDeflCmd_  = integratorP_ + apGains_.Kp * pFiltered_;
    pitchDeflCmd_ = integratorQ_ + apGains_.Kq * qFiltered_;
    yawDeflCmd_   = integratorR_ + apGains_.Kr * rFiltered_;

    // Compute control decoupling
    rollDeflCmdDecoupled_  = apGains_.KRR * rollDeflCmd_ + apGains_.KRP * pitchDeflCmd_ + apGains_.KRY * yawDeflCmd_;
    pitchDeflCmdDecoupled_ = apGains_.KPR * rollDeflCmd_ + apGains_.KPP * pitchDeflCmd_ + apGains_.KPY * yawDeflCmd_;
    yawDeflCmdDecoupled_   = apGains_.KYR * rollDeflCmd_ + apGains_.KYP * pitchDeflCmd_ + apGains_.KYY * yawDeflCmd_;

    // Limit control surface commands
    maxDefl_ = std::fabs( rollDeflCmdDecoupled_ ) + COS45 * ( std::fabs( pitchDeflCmdDecoupled_ ) + std::fabs( yawDeflCmdDecoupled_ ) );

    if ( maxDefl_ > finStallLimit_ )
    {
        const float deflRatio = finStallLimit_ / maxDefl_;

        rollDeflCmdDecLimited_  = rollDeflCmdDecoupled_ * deflRatio;
        pitchDeflCmdDecLimited_ = pitchDeflCmdDecoupled_ * deflRatio;
        yawDeflCmdDecLimited_   = yawDeflCmdDecoupled_ * deflRatio;

        antiWindup_ = true;
    }
    else
    {
        rollDeflCmdDecLimited_  = rollDeflCmdDecoupled_;
        pitchDeflCmdDecLimited_ = pitchDeflCmdDecoupled_;
        yawDeflCmdDecLimited_   = yawDeflCmdDecoupled_;

        antiWindup_ = false;
    }

    // Compute control surface commands pre MSFR
    // rollDeflCmdLtdPreMSFR_  = rollDeflCmdDecLimited_;
    // pitchDeflCmdLtdPreMSFR_ = pitchDeflCmdDecLimited_;
    // yawDeflCmdLtdPreMSFR_   = yawDeflCmdDecLimited_;

    if ( sysIdEnable_ )
    {
        ApplySysIdInput( inData );
    }

    // Mix deflections to fin commands
    fin1Cmd_ = rollDeflCmdDecLimited_ + COS45 * (  pitchDeflCmdDecLimited_ - yawDeflCmdDecLimited_ );
    fin2Cmd_ = rollDeflCmdDecLimited_ + COS45 * (  pitchDeflCmdDecLimited_ + yawDeflCmdDecLimited_ );
    fin3Cmd_ = rollDeflCmdDecLimited_ + COS45 * ( -pitchDeflCmdDecLimited_ + yawDeflCmdDecLimited_ );
    fin4Cmd_ = rollDeflCmdDecLimited_ + COS45 * ( -pitchDeflCmdDecLimited_ - yawDeflCmdDecLimited_ );

    // Reset integrator states when fin deflection limit is exceeded
    if ( antiWindup_ )
    {
        integratorP_ = apGains_.IKRR * rollDeflCmdDecLimited_ + apGains_.IKRP * pitchDeflCmdDecLimited_ + apGains_.IKRY * yawDeflCmdDecLimited_ - apGains_.Kp * pFiltered_;
        integratorQ_ = apGains_.IKPR * rollDeflCmdDecLimited_ + apGains_.IKPP * pitchDeflCmdDecLimited_ + apGains_.IKPY * yawDeflCmdDecLimited_ - apGains_.Kq * qFiltered_;
        integratorR_ = apGains_.IKYR * rollDeflCmdDecLimited_ + apGains_.IKYP * pitchDeflCmdDecLimited_ + apGains_.IKYY * yawDeflCmdDecLimited_ - apGains_.Kr * rFiltered_;
    }
}

void HighRateAutopilotAlgorithm::ProcessImuData( const HighRateAutopilotTypes::InData& inData )
{
    aX_ = inData.measAccel[0] / myMath::Constants::GRAVITY_ACCEL;
    aY_ = (  COS45 * inData.measAccel[1] + SIN45 * inData.measAccel[2] ) / myMath::Constants::GRAVITY_ACCEL;
    aZ_ = ( -SIN45 * inData.measAccel[1] + COS45 * inData.measAccel[2] ) / myMath::Constants::GRAVITY_ACCEL;

    p_ =  inData.measOmega[0];
    q_ =  COS45 * inData.measOmega[1] + SIN45 * inData.measOmega[2];
    r_ = -SIN45 * inData.measOmega[1] + COS45 * inData.measOmega[2];

    u_ = inData.measVel[0];
    v_ =  COS45 * inData.measVel[1] + SIN45 * inData.measVel[2];
    w_ = -SIN45 * inData.measVel[1] + COS45 * inData.measVel[2];
}


void HighRateAutopilotAlgorithm::ProcessGuidanceCommands( const HighRateAutopilotTypes::InData& inData )
{
    if ( adaptGLimits_ )
    {
        if ( maxDefl_ > AGA_FIN_HI_LIMIT * finStallLimit_
                && ( std::fabs( rollError_ ) > AGA_ROLL_ERR_LIMIT || std::fabs( azError_ ) > AGA_ACCEL_ERROR_LIMIT * maxG_ * maxGSF_ ) )
        {
            maxGSF_ = std::max( AGA_SF_LO_LIMIT, maxGSF_ - AGA_COUNT_DOWN_INC );
        }
        else if ( maxDefl_ < AGA_FIN_LO_LIMIT * finStallLimit_ )
        {
            maxGSF_ = std::min( AGA_SF_HI_LIMIT, maxGSF_ + AGA_COUNT_UP_INC );
        }
    }
    else
    {
        maxGSF_ = 1.0f;
    }

    ayCmd_ = (  COS45 * inData.guidanceAccelCmdYbody + SIN45 * inData.guidanceAccelCmdZbody ) / myMath::Constants::GRAVITY_ACCEL;
    azCmd_ = ( -SIN45 * inData.guidanceAccelCmdYbody + COS45 * inData.guidanceAccelCmdZbody ) / myMath::Constants::GRAVITY_ACCEL;

    cmdMagGs_ = std::sqrt( ayCmd_ * ayCmd_ + azCmd_ * azCmd_ );

    if ( cmdMagGs_ > maxG_ * maxGSF_ )
    {
        const float gCmdRatio = maxG_ * maxGSF_ / cmdMagGs_;

        ayCmdLimited_ = ayCmd_ * gCmdRatio;
        azCmdLimited_ = azCmd_ * gCmdRatio;
    }
    else
    {
        ayCmdLimited_ = ayCmd_;
        azCmdLimited_ = azCmd_;
    }

    ayCmdRateLimited_ += std::max( -accelCmdRateLimit_ * APConstants::AP_HIGH_RATE_DELTA_T, std::min( accelCmdRateLimit_ * APConstants::AP_HIGH_RATE_DELTA_T, ayCmdLimited_ - ayCmdRateLimited_ ) );
    azCmdRateLimited_ += std::max( -accelCmdRateLimit_ * APConstants::AP_HIGH_RATE_DELTA_T, std::min( accelCmdRateLimit_ * APConstants::AP_HIGH_RATE_DELTA_T, azCmdLimited_ - azCmdRateLimited_ ) );
}

void HighRateAutopilotAlgorithm::ApplySysIdInput( const HighRateAutopilotTypes::InData& inData )
{
    if ( inData.time >= sysIdDelay_ )
    {
        if ( sysIdChirp_ && inData.time <= ( sysIdDelay_ + sysIdChirpDuration_ ) )
        {
            // Smooth chirp
            const float sweepTime = inData.time - sysIdDelay_;
            const float c = ( sysIdFreqEnd_ - sysIdFreqStart_ ) / sysIdChirpDuration_;
            const float sysIdSignal = sysIdMag_ * std::sin( 2.0f * myMath::Constants::PI * sweepTime * ( c * sweepTime / 2.0f + sysIdFreqStart_ ) );

            if ( sysIdChannel_ == 1 )
            {
                rollDeflCmdDecLimited_ += sysIdSignal;
            }
            else if ( sysIdChannel_ == 2 )
            {
                pitchDeflCmdDecLimited_ += sysIdSignal;
            }
            else if ( sysIdChannel_ == 3 )
            {
                yawDeflCmdDecLimited_ += sysIdSignal;
            }
        }
        else
        {
            // Frequency steps
            const float sweepTime = inData.time - sysIdDelay_;
            const float sysIdSignal = sysIdMag_ * std::sin( 2.0f * myMath::Constants::PI * sysIdFreq_ * sweepTime );

            if ( sysIdChannel_ == 1 )
            {
                rollDeflCmdDecLimited_ += sysIdSignal;
            }
            else if ( sysIdChannel_ == 2 )
            {
                pitchDeflCmdDecLimited_ += sysIdSignal;
            }
            else if ( sysIdChannel_ == 3 )
            {
                yawDeflCmdDecLimited_ += sysIdSignal;
            }
        }
    }
}

void HighRateAutopilotAlgorithm::BuildOutput( HighRateAutopilotTypes::OutData& outData )
{
    outData.fin1Cmd = fin1Cmd_;
    outData.fin2Cmd = fin2Cmd_;
    outData.fin3Cmd = fin3Cmd_;
    outData.fin4Cmd = fin4Cmd_;

    outData.scsDelta1Cmd = scsDelta1Cmd_;
    outData.scsDelta2Cmd = scsDelta2Cmd_;
    outData.scsDelta3Cmd = scsDelta3Cmd_;
    outData.scsDelta4Cmd = scsDelta4Cmd_;
}