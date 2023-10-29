#ifndef E25BC965_48E9_4610_9EB1_F46FB325D634
#define E25BC965_48E9_4610_9EB1_F46FB325D634

#include "MessageContainer.h"
#include "Payload.h"
#include "Decorators.h"

#include "AutopilotMsg.h"
#include "CtrlSurfMsg.h"

namespace CtrlSurfTypes
{
    struct InData : Intf::MessageContainer<
        InputPayload< AutopilotMsg, Persistent >
    >
    {};

    struct OutData : Intf::MessageContainer<
        OutputPayload< CtrlSurfMsg >
    >
    {};
}

#endif /* E25BC965_48E9_4610_9EB1_F46FB325D634 */
