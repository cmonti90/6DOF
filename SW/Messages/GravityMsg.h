#ifndef A9459157_330F_44B7_8744_E91039735134
#define A9459157_330F_44B7_8744_E91039735134

#include "MessagePayloadTemplate.hxx"

#include "MsgIds.hpp"

struct GravityData
{
    double forceBody_raw[3];

    void Default()
    {
        for (int i = 0; i < 3; i++)
        {
            forceBody_raw[i] = 0.0;
        }
    }

    GravityData() : forceBody_raw()
    {
        Default();
    }
};

MESSAGE_PAYLOAD(GravityMsg, GravityData, GravityMsgId)

#endif /* A9459157_330F_44B7_8744_E91039735134 */
