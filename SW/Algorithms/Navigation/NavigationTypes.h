#ifndef A90D8B4C_82E1_4577_8952_A8CEB7364970
#define A90D8B4C_82E1_4577_8952_A8CEB7364970

#include "MessageContainer.h"
#include "Payload.h"

#include "AeroMsg.h"

namespace NavTypes
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


#endif /* A90D8B4C_82E1_4577_8952_A8CEB7364970 */
