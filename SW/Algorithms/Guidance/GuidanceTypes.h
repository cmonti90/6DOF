#ifndef D4FEDE68_DEE3_4F83_BC4B_5D87A427FDB8
#define D4FEDE68_DEE3_4F83_BC4B_5D87A427FDB8

#include "MessageContainer.h"
#include "Payload.h"

#include "AeroMsg.h"

namespace GuidanceTypes
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

#endif /* D4FEDE68_DEE3_4F83_BC4B_5D87A427FDB8 */
