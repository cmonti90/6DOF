#ifndef AAC50CF4_BB26_4D29_943A_B3539AC46DCB
#define AAC50CF4_BB26_4D29_943A_B3539AC46DCB

#include "MessageContainer.h"
#include "Payload.h"

#include "ImuMsg.h"

#include "ImuDataSerialization.h"

namespace IMUTypes
{
    struct OutData : Intf::MessageContainer<
        OutputPayload< ImuMsg, Serialize >
    >
    {};
}

#endif /* AAC50CF4_BB26_4D29_943A_B3539AC46DCB */
