#ifndef E9EF5EDF_D4A9_4BE8_A659_CB7E4C2F405F
#define E9EF5EDF_D4A9_4BE8_A659_CB7E4C2F405F

#include "MessageContainer.h"
#include "Payload.h"
#include "Decorators.h"

#include "AeroMsg.h"
#include "EngineMsg.h"
#include "EomMsg.h"
#include "GravityMsg.h"
#include "MassPropMsg.h"

#include "GravityDataSerialization.h"
#include "AeroDataSerialization.h"
#include "EngineDataSerialization.h"
#include "EomDataSerialization.h"
#include "MassPropDataSerialization.h"

namespace EomTypes
{
    struct InData : Intf::MessageContainer <
        InputPayload<AeroMsg, Deserialize, Persistent>,
        InputPayload<EngineMsg, Deserialize>,
        InputPayload<GravityMsg, Deserialize>,
        InputPayload<MassPropMsg, Deserialize, Persistent>
        >
    {};

    struct OutData : Intf::MessageContainer <
        OutputPayload<EomMsg, Serialize>
        >
    {};
}

#endif /* E9EF5EDF_D4A9_4BE8_A659_CB7E4C2F405F */
