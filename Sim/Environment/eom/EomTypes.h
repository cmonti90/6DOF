#ifndef E9EF5EDF_D4A9_4BE8_A659_CB7E4C2F405F
#define E9EF5EDF_D4A9_4BE8_A659_CB7E4C2F405F

#include "MessageContainer.h"
#include "Payload.h"

#include "AeroMsg.h"
#include "EngineMsg.h"
#include "EomMsg.h"
#include "GravityMsg.h"
#include "MassPropMsg.h"

namespace EomTypes
{
    struct InData : Intf::MessageContainer<
        InputPayload<AeroMsg>,
        InputPayload<EngineMsg>,
        InputPayload<GravityMsg>,
        InputPayload<MassPropMsg>
    >
    {};

    struct OutData : Intf::MessageContainer<
        OutputPayload<EomMsg>
    >
    {};
}

#endif /* E9EF5EDF_D4A9_4BE8_A659_CB7E4C2F405F */
