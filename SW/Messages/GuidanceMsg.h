#ifndef GUIDANCE_MSG_H
#define GUIDANCE_MSG_H

#include "MessagePayloadTemplate.hxx"

#include "MsgIds.hpp"

struct GuidanceData
{
    float guidanceAccelCmdYbody;
    float guidanceAccelCmdZbody;

    float cmdRoll;
    float integratedRollRate;

    void Default()
    {
        guidanceAccelCmdYbody = 0.0f;
        guidanceAccelCmdZbody = 0.0f;

        cmdRoll = 0.0f;
        integratedRollRate = 0.0f;
    }

    GuidanceData()
        : guidanceAccelCmdYbody()
        , guidanceAccelCmdZbody()
        , cmdRoll()
        , integratedRollRate()
    {
        Default();
    }
};

MESSAGE_PAYLOAD( GuidanceMsg, GuidanceData, GuidanceMsgId )

#endif // GUIDANCE_MSG_H
