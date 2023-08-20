#ifndef E2B9B195_F133_4866_A2AF_94862368096D
#define E2B9B195_F133_4866_A2AF_94862368096D

#include "MessageContainer.h"
#include "Payload.h"

#include "AeroMsg.h"

namespace AutopilotTypes
{
    struct InData : Intf::MessageContainer<
        InputPayload<AeroMsg>
    >
    {};

    struct OutData : Intf::MessageContainer<
        OutputPayload<AeroMsg>
    >
    {};
}

#endif /* E2B9B195_F133_4866_A2AF_94862368096D */
