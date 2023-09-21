#ifndef IMUTYPES_H
#define IMUTYPES_H

#include "MessageContainer.h"
#include "Payload.h"
#include "Decorators.h"

#include "ImuMsg.h"
#include "EomMsg.h"

#include "EomDataSerialization.h"

namespace ImuTypes
{
    struct InData : Intf::MessageContainer<
        InputPayload<EomMsg, Deserialize>
    >
    {};

    struct OutData : Intf::MessageContainer<
        OutputPayload<ImuMsg>
    >
    {};
}

#endif /* IMUTYPES_H */
