#ifndef E25BC965_48E9_4610_9EB1_F46FB325D634
#define E25BC965_48E9_4610_9EB1_F46FB325D634

#include "MessageContainer.h"
#include "Payload.h"

#include "AeroMsg.h"

namespace EngineTypes
{
    struct InData : Intf::MessageContainer<
        InputPayload<AeroMsg>
    >
    {};

    struct OutData : Intf::MessageContainer<
        OutputPayload<AeroMsg>
    >
    {};
}

#endif /* E25BC965_48E9_4610_9EB1_F46FB325D634 */
