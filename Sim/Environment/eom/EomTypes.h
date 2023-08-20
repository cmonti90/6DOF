#ifndef E9EF5EDF_D4A9_4BE8_A659_CB7E4C2F405F
#define E9EF5EDF_D4A9_4BE8_A659_CB7E4C2F405F

#include "MessageContainer.h"
#include "Payload.h"

#include "AeroMsg.h"
#include "EngineMsg.h"

namespace EomTypes
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

#endif /* E9EF5EDF_D4A9_4BE8_A659_CB7E4C2F405F */
