#ifndef B0EB4116_CB1C_4110_A642_7A06E863FA04
#define B0EB4116_CB1C_4110_A642_7A06E863FA04

#include "MessagePayloadTemplate.hxx"

#include "MsgIds.hpp"

#include "Vector.h"

struct EngineData
{
    double forceBody_raw[3];
    double momentBody_raw[3];

    void Default()
    {
        for (int i = 0; i < 3; i++)
        {
            forceBody_raw[i] = 0.0;
            momentBody_raw[i] = 0.0;
        }
    }

    EngineData() : forceBody_raw(), momentBody_raw()
    {
        Default();
    }
};

MESSAGE_PAYLOAD(EngineMsg, EngineData, EngineMsgId)

#endif /* B0EB4116_CB1C_4110_A642_7A06E863FA04 */
