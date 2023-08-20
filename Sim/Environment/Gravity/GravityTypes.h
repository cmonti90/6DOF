#ifndef GRAVITYTYPES_H
#define GRAVITYTYPES_H

#include "MessageContainer.h"
#include "Payload.h"

#include "EomMsg.h"
#include "GravityMsg.h"

namespace GravityTypes
{
    struct InData : Intf::MessageContainer<
        InputPayload<EomMsg>
    >
    {};

    struct OutData : Intf::MessageContainer<
        OutputPayload<GravityMsg>
    >
    {};
}

#endif /* GRAVITYTYPES_H */
