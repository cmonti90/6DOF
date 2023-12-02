#ifndef GRAVITYTYPES_H
#define GRAVITYTYPES_H

#include "MessageContainer.h"
#include "Payload.h"

#include "EomMsg.h"
#include "GravityMsg.h"
#include "MassPropMsg.h"

#include "EomDataSerialization.h"
#include "GravityDataSerialization.h"
#include "MassPropDataSerialization.h"

namespace GravityTypes
{
    struct InData : Intf::MessageContainer <
        InputPayload< EomMsg     , Deserialize >,
        InputPayload< MassPropMsg, Deserialize >
        >
    {};

    struct OutData : Intf::MessageContainer <
        OutputPayload< GravityMsg, Serialize >
        >
    {};
}

#endif /* GRAVITYTYPES_H */
