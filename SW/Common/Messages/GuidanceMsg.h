#ifndef BA4F55A0_04C9_4204_90F7_54C14F0C45D3
#define BA4F55A0_04C9_4204_90F7_54C14F0C45D3

#include "Message.h"

#include "MessagePayloadTemplate.hxx"

struct GuidanceData
{
    double force[3];
    double moment[3];

    void Default()
    {
        for (unsigned int i{ 0u }; i < 3u; ++i)
        {
            force[i] = 0.0;
            moment[i] = 0.0;
        }
    }

    GuidanceData& operator=( const GuidanceData& other )
    {
        for (unsigned int i{ 0u }; i < 3u; ++i)
        {
            force[i] = other.force[i];
            moment[i] = other.moment[i];
        }

        return *this;
    }

    GuidanceData() : force(), moment()
    {
        Default();
    }

    GuidanceData( const GuidanceData& other ) : force(), moment()
    {
        for (unsigned int i{ 0u }; i < 3u; ++i)
        {
            force[i] = other.force[i];
            moment[i] = other.moment[i];
        }
    }
};

MESSAGE_PAYLOAD(GuidanceMsg, GuidanceData, 70)


#endif /* BA4F55A0_04C9_4204_90F7_54C14F0C45D3 */
