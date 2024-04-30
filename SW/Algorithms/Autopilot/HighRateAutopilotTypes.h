#ifndef HIGHRATEAUTOPILOTTYPES_H
#define HIGHRATEAUTOPILOTTYPES_H

#include "MessageContainer.h"
#include "Payload.h"
#include "Decorators.h"

#include "GuidanceMsg.h"
#include "HighRateAutopilotMsg.h"
#include "ImuMsg.h"
#include "LowRateAutopilotMsg.h"
#include "NavMsg.h"

#include "ImuDataSerialization.h"
#include "LowRateApSerialization.h"
#include "NavDataSerialization.h"

namespace HighRateAutopilotTypes
{
    struct InData : Intf::MessageContainer<
        InputPayload< GuidanceMsg        ,              Persistent >,
        InputPayload< ImuMsg             , Deserialize, Persistent >,
        InputPayload< LowRateAutopilotMsg, Deserialize, Persistent >,
        InputPayload< NavMsg             , Deserialize, Persistent >
    >
    {};

    struct OutData : Intf::MessageContainer<
        OutputPayload< HighRateAutopilotMsg >
    >
    {};
}

#endif // HIGHRATEAUTOPILOTTYPES_H
