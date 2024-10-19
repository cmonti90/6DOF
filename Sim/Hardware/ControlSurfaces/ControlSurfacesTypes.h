#ifndef CONTROL_SURFACE_TYPES_H
#define CONTROL_SURFACE_TYPES_H

#include "MessageContainer.h"
#include "Payload.h"
#include "Decorators.h"

#include "HighRateAutopilotMsg.h"

namespace CtrlSurfTypes
{
    struct InData : Intf::MessageContainer<
        InputPayload< HighRateAutopilotMsg, Persistent >
    >
    {};
}

#endif // CONTROL_SURFACE_TYPES_H
