#ifndef B04312C8_8F23_4DA1_B20F_8816627483AE
#define B04312C8_8F23_4DA1_B20F_8816627483AE

#include "MessageContainer.h"
#include "Payload.h"

#include "AeroMsg.h"

namespace AeroTypes
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

#endif /* B04312C8_8F23_4DA1_B20F_8816627483AE */
