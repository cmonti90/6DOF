#ifndef C620E104_6423_4144_8FA1_0E776A28A042
#define C620E104_6423_4144_8FA1_0E776A28A042

#include "MessageContainer.h"
#include "Payload.h"

#include "AeroMsg.h"
#include "EngineMsg.h"

namespace MassPropTypes
{
    struct InData : Intf::MessageContainer<
        InputPayload<AeroMsg>,
        InputPayload<EngineMsg>
    >
    {};

    struct OutData : Intf::MessageContainer<
        OutputPayload<AeroMsg>
    >
    {};
}

#endif /* C620E104_6423_4144_8FA1_0E776A28A042 */
