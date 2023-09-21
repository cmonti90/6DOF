#ifndef E379D5A1_B7C3_46B7_9DE5_37D4C17FF27D
#define E379D5A1_B7C3_46B7_9DE5_37D4C17FF27D

#include "MessagePayloadTemplate.hxx"

#include "MsgIds.hpp"

struct AeroData
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

    AeroData() : forceBody_raw(), momentBody_raw()
    {
        Default();
    }
};

MESSAGE_PAYLOAD(AeroMsg, AeroData, AeroMsgId)

#endif /* E379D5A1_B7C3_46B7_9DE5_37D4C17FF27D */
