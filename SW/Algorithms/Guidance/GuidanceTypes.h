#ifndef D4FEDE68_DEE3_4F83_BC4B_5D87A427FDB8
#define D4FEDE68_DEE3_4F83_BC4B_5D87A427FDB8

#include "MessageContainer.h"
#include "Payload.h"

#include "NavMsg.h"
#include "GuidanceMsg.h"

namespace GuidanceTypes
{
    struct InData : Intf::MessageContainer<
        InputPayload<NavMsg>
    >
    {};

    struct OutData : Intf::MessageContainer<
        OutputPayload<GuidanceMsg>
    >
    {};
}

#endif /* D4FEDE68_DEE3_4F83_BC4B_5D87A427FDB8 */
