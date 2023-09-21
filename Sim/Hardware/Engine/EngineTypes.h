#ifndef E25BC965_48E9_4610_9EB1_F46FB325D634
#define E25BC965_48E9_4610_9EB1_F46FB325D634

#include "MessageContainer.h"
#include "Payload.h"

#include "AutopilotMsg.h"
#include "EngineMsg.h"

#include "EngineDataSerialization.h"

namespace EngineTypes
{
    struct InData : Intf::MessageContainer<
        InputPayload<AutopilotMsg>
    >
    {};

    struct OutData : Intf::MessageContainer<
        OutputPayload<EngineMsg, Serialize>
    >
    {};
}

#endif /* E25BC965_48E9_4610_9EB1_F46FB325D634 */
