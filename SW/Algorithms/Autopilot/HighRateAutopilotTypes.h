#ifndef E2B9B195_F133_4866_A2AF_94862368096D
#define E2B9B195_F133_4866_A2AF_94862368096D

#include "MessageContainer.h"
#include "Payload.h"
#include "Decorators.h"

#include "AutopilotMsg.h"
#include "GuidanceMsg.h"
#include "NavMsg.h"

#include "NavDataSerialization.h"

namespace HighRateAutopilotTypes
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

#endif /* E2B9B195_F133_4866_A2AF_94862368096D */
