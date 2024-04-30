#ifndef AUTOPILOTCONSTANTS_H
#define AUTOPILOTCONSTANTS_H

#include "myMathConstants.h"

namespace APConstants
{
    constexpr float AP_HIGH_RATE = 600.0f;
    constexpr float AP_HIGH_RATE_DELTA_T = 1.0f / AP_HIGH_RATE;

    constexpr float ROLL_CMD_RATE_LIMIT = 250.0 * myMath::Constants::DEG_TO_RAD;
    constexpr float MTAP_DEFLECTION_LIMIT = 30.0 * myMath::Constants::DEG_TO_RAD;

} // namespace APConstants

#endif // AUTOPILOTCONSTANTS_H