#ifndef LOWRATEAUTOPILOTTYPES_H
#define LOWRATEAUTOPILOTTYPES_H

#include "MessageContainer.h"
#include "Payload.h"
#include "Decorators.h"

#include "GuidanceMsg.h"
#include "HighRateAutopilotMsg.h"
#include "LowRateAutopilotMsg.h"
#include "NavMsg.h"

#include "LowRateApSerialization.h"
#include "NavDataSerialization.h"

namespace LowRateAutopilotTypes
{
    struct InData : Intf::MessageContainer<
        InputPayload< GuidanceMsg                                   >,
        InputPayload< NavMsg              , Deserialize, Persistent >
    >
    {};

    struct OutData : Intf::MessageContainer<
        OutputPayload< LowRateAutopilotMsg, Serialize >
    >
    {};
}

#endif // LOWRATEAUTOPILOTTYPES_H
