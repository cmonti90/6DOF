#ifndef B25DAB41_D1E7_4D25_9D19_0F2F59867A12
#define B25DAB41_D1E7_4D25_9D19_0F2F59867A12

#include "MessagePayloadTemplate.hxx"

#include "MsgIds.hpp"

struct NavData
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

    NavData() : force(), moment()
    {
        Default();
    }
};

MESSAGE_PAYLOAD(NavMsg, NavData, NavMsgId)


#endif /* B25DAB41_D1E7_4D25_9D19_0F2F59867A12 */
