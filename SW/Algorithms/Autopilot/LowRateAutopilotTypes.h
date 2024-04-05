#ifndef LOWRATEAUTOPILOTTYPES_H
#define LOWRATEAUTOPILOTTYPES_H

#include "MessageContainer.h"
#include "Payload.h"
#include "Decorators.h"

#include "AutopilotMsg.h"
#include "GuidanceMsg.h"
#include "NavMsg.h"

#include "NavDataSerialization.h"

namespace LowRateAutopilotTypes
{
    struct InData : Intf::MessageContainer<
        InputPayload< GuidanceMsg                          >,
        InputPayload< NavMsg     , Deserialize, Persistent >
    >
    {};

    struct OutData : Intf::MessageContainer<
        OutputPayload< AutopilotMsg >
    >
    {};
}

#endif // LOWRATEAUTOPILOTTYPES_H
