#ifndef D9E6A0CB_3DA1_4BA9_A51B_80A2E9FD2C7B
#define D9E6A0CB_3DA1_4BA9_A51B_80A2E9FD2C7B

#include "MessagePayloadTemplate.hxx"

#include "MsgIds.hpp"

struct GRAMData
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

    GRAMData() : forceBody_raw(), momentBody_raw()
    {
        Default();
    }
};

MESSAGE_PAYLOAD(GRAMMsg, GRAMData, GRAMMsgId)

#endif /* D9E6A0CB_3DA1_4BA9_A51B_80A2E9FD2C7B */
