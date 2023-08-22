#ifndef A9459157_330F_44B7_8744_E91039735134
#define A9459157_330F_44B7_8744_E91039735134

#include "MessagePayloadTemplate.hxx"

#include "MsgIds.hpp"

#include <Vector.h>

struct GravityData
{
    myMath::Vector3d forceBody;

    void Default()
    {
        forceBody = 0.0;
    }

    GravityData &operator=(const GravityData &other)
    {
        forceBody = other.forceBody;

        return *this;
    }

    GravityData() : forceBody()
    {
        Default();
    }

    GravityData(const GravityData &other) : forceBody(other.forceBody)
    {
    }
};

MESSAGE_PAYLOAD(GravityMsg, GravityData, GravityMsgId)

#endif /* A9459157_330F_44B7_8744_E91039735134 */
