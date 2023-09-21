#ifndef C620E104_6423_4144_8FA1_0E776A28A042
#define C620E104_6423_4144_8FA1_0E776A28A042

#include "MessageContainer.h"
#include "Payload.h"

#include "EngineMsg.h"
#include "MassPropMsg.h"
#include "MassPropDataSerialization.h"

namespace MassPropTypes
{
    struct InData : Intf::MessageContainer<
        InputPayload<EngineMsg>
    >
    {};

    struct OutData : Intf::MessageContainer<
        OutputPayload<MassPropMsg, Serialize>
    >
    {};
}

#endif /* C620E104_6423_4144_8FA1_0E776A28A042 */
