#ifndef B04312C8_8F23_4DA1_B20F_8816627483AE
#define B04312C8_8F23_4DA1_B20F_8816627483AE

#include "MessageContainer.h"
#include "Payload.h"

#include "AeroMsg.h"
#include "CtrlSurfMsg.h"
#include "EomMsg.h"

namespace AeroTypes
{
    struct InData : Intf::MessageContainer<
        InputPayload<EomMsg>,
        InputPayload<CtrlSurfMsg>
    >
    {};

    struct OutData : Intf::MessageContainer<
        OutputPayload<AeroMsg>
    >
    {};
}

#endif /* B04312C8_8F23_4DA1_B20F_8816627483AE */
