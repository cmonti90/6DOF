#ifndef B04312C8_8F23_4DA1_B20F_8816627483AE
#define B04312C8_8F23_4DA1_B20F_8816627483AE

#include "MessageContainer.h"
#include "Payload.h"

#include "AeroMsg.h"
#include "CtrlSurfMsg.h"
#include "EomMsg.h"
#include "GRAMMsg.h"

#include "AeroDataSerialization.h"
#include "EomDataSerialization.h"
#include "GravityDataSerialization.h"
#include "GRAMDataSerialization.h"

namespace AeroTypes
{
    struct InData : Intf::MessageContainer <
        InputPayload< EomMsg,      Deserialize             >,
        InputPayload< CtrlSurfMsg,              Persistent >,
        InputPayload< GRAMMsg,     Deserialize             >
        >
    {};

    struct OutData : Intf::MessageContainer <
        OutputPayload< AeroMsg, Serialize >
        >
    {};
}

#endif /* B04312C8_8F23_4DA1_B20F_8816627483AE */
