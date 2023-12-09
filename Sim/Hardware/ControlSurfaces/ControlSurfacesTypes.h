#ifndef BDE58E5F_531A_4559_8B5D_23221BF7D828
#define BDE58E5F_531A_4559_8B5D_23221BF7D828
#ifndef E25BC965_48E9_4610_9EB1_F46FB325D634
#define E25BC965_48E9_4610_9EB1_F46FB325D634

#include "MessageContainer.h"
#include "Payload.h"
#include "Decorators.h"

#include "AutopilotMsg.h"

namespace CtrlSurfTypes
{
    struct InData : Intf::MessageContainer<
        InputPayload< AutopilotMsg, Persistent >
    >
    {};
}

#endif /* E25BC965_48E9_4610_9EB1_F46FB325D634 */


#endif /* BDE58E5F_531A_4559_8B5D_23221BF7D828 */
