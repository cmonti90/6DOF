#ifndef IMUTYPES_H
#define IMUTYPES_H

#include "MessageContainer.h"
#include "Payload.h"

#include "ImuMsg.h"
#include "EomMsg.h"

namespace ImuTypes
{
    struct InData : Intf::MessageContainer<
        InputPayload<EomMsg>
    >
    {};

    struct OutData : Intf::MessageContainer<
        OutputPayload<ImuMsg>
    >
    {};
}

#endif /* IMUTYPES_H */
