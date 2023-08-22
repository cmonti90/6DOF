#ifndef BA4F55A0_04C9_4204_90F7_54C14F0C45D3
#define BA4F55A0_04C9_4204_90F7_54C14F0C45D3

#include "MessagePayloadTemplate.hxx"

#include "MsgIds.hpp"

struct GuidanceData
{
    double guidanceAccelCmdXbody;
    double guidanceAccelCmdYbody;
    double guidanceAccelCmdZbody;

    void Default()
    {
        guidanceAccelCmdXbody = 0.0;
        guidanceAccelCmdYbody = 0.0;
        guidanceAccelCmdZbody = 0.0;
    }

    GuidanceData &operator=(const GuidanceData &other)
    {
        guidanceAccelCmdXbody = other.guidanceAccelCmdXbody;
        guidanceAccelCmdYbody = other.guidanceAccelCmdYbody;
        guidanceAccelCmdZbody = other.guidanceAccelCmdZbody;

        return *this;
    }

    GuidanceData() : guidanceAccelCmdXbody(), guidanceAccelCmdYbody(), guidanceAccelCmdZbody()
    {
        Default();
    }

    GuidanceData(const GuidanceData &other) : guidanceAccelCmdXbody(), guidanceAccelCmdYbody(), guidanceAccelCmdZbody()
    {
        guidanceAccelCmdXbody = other.guidanceAccelCmdXbody;
        guidanceAccelCmdYbody = other.guidanceAccelCmdYbody;
        guidanceAccelCmdZbody = other.guidanceAccelCmdZbody;
    }
};

MESSAGE_PAYLOAD(GuidanceMsg, GuidanceData, GuidanceMsgId)

#endif /* BA4F55A0_04C9_4204_90F7_54C14F0C45D3 */
