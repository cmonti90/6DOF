#ifndef A90D8B4C_82E1_4577_8952_A8CEB7364970
#define A90D8B4C_82E1_4577_8952_A8CEB7364970

#include "MessageContainer.h"
#include "Payload.h"

#include "ImuMsg.h"
#include "NavMsg.h"

#include "NavDataSerialization.h"

namespace NavTypes
{
    struct InData : Intf::MessageContainer<
        InputPayload<ImuMsg>
    >
    {};

    struct OutData : Intf::MessageContainer<
        OutputPayload<NavMsg, Serialize>
    >
    {};
}


#endif /* A90D8B4C_82E1_4577_8952_A8CEB7364970 */
