#ifndef DC3542B2_0591_4E79_BA3F_E310DAD23B75
#define DC3542B2_0591_4E79_BA3F_E310DAD23B75

#include "MessageContainer.h"
#include "Payload.h"
#include "Decorators.h"

#include "EomMsg.h"
#include "MassPropMsg.h"
#include "GRAMMsg.h"

#include "EomDataSerialization.h"
#include "MassPropDataSerialization.h"
#include "GRAMDataSerialization.h"

namespace GRAMTypes
{
    struct InData : Intf::MessageContainer <
        InputPayload<MassPropMsg, Deserialize, Persistent>,
        InputPayload<EomMsg, Deserialize, Persistent>
        >
    {};

    struct OutData : Intf::MessageContainer <
        OutputPayload<GRAMMsg, Serialize>
        >
    {};
}

#endif /* DC3542B2_0591_4E79_BA3F_E310DAD23B75 */
