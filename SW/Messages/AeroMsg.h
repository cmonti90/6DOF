#ifndef E379D5A1_B7C3_46B7_9DE5_37D4C17FF27D
#define E379D5A1_B7C3_46B7_9DE5_37D4C17FF27D

#include "MessagePayloadTemplate.hxx"

#include "MsgIds.hpp"

#include "Vector.h"

struct AeroData
{
    myMath::Vector3d forceBody;
    myMath::Vector3d momentBody;

    void Default()
    {
        forceBody = 0.0;
        momentBody = 0.0;
    }

    AeroData &operator=(const AeroData &other)
    {
        forceBody = other.forceBody;
        momentBody = other.momentBody;

        return *this;
    }

    AeroData() : forceBody(), momentBody()
    {
        Default();
    }

    AeroData(const AeroData &other) : forceBody(other.forceBody), momentBody(other.momentBody)
    {
    }
};

MESSAGE_PAYLOAD(AeroMsg, AeroData, AeroMsgId)

#endif /* E379D5A1_B7C3_46B7_9DE5_37D4C17FF27D */
