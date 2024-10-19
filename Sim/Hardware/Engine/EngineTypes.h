#ifndef E25BC965_48E9_4610_9EB1_F46FB325D634
#define E25BC965_48E9_4610_9EB1_F46FB325D634

#include "MessageContainer.h"
#include "Payload.h"

#include "HighRateAutopilotMsg.h"

namespace EngineTypes
{
    struct InData : Intf::MessageContainer<
        InputPayload<HighRateAutopilotMsg>
    >
    {};
}

#endif /* E25BC965_48E9_4610_9EB1_F46FB325D634 */
