#ifndef B0EB4116_CB1C_4110_A642_7A06E863FA04
#define B0EB4116_CB1C_4110_A642_7A06E863FA04

#include "MessagePayloadTemplate.hxx"

#include "MsgIds.hpp"

#include "Vector.h"

struct EngineData
{
    myMath::Vector3d forceBody;
    myMath::Vector3d momentBody;

    void Default()
    {
        forceBody = 0.0;
        momentBody = 0.0;
    }

    EngineData &operator=(const EngineData &other)
    {
        forceBody = other.forceBody;
        momentBody = other.momentBody;

        return *this;
    }

    EngineData() : forceBody(), momentBody()
    {
        Default();
    }

    EngineData(const EngineData &other) : forceBody(other.forceBody), momentBody(other.momentBody)
    {
    }
};

MESSAGE_PAYLOAD(EngineMsg, EngineData, EngineMsgId)

#endif /* B0EB4116_CB1C_4110_A642_7A06E863FA04 */
