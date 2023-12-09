#ifndef AAC50CF4_BB26_4D29_943A_B3539AC46DCB
#define AAC50CF4_BB26_4D29_943A_B3539AC46DCB

#include "MessageContainer.h"
#include "Payload.h"

#include "ImuMsg.h"

namespace IMUTypes
{
    struct OutData : Intf::MessageContainer<
        OutputPayload< ImuMsg >
    >
    {};
}

#endif /* AAC50CF4_BB26_4D29_943A_B3539AC46DCB */
