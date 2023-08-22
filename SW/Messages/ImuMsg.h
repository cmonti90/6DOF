#ifndef F826EEC0_1BBA_4DB7_9903_1AD431D6F7E0
#define F826EEC0_1BBA_4DB7_9903_1AD431D6F7E0

#include "MessagePayloadTemplate.hxx"

#include "MsgIds.hpp"

struct ImuData
{
    double accelXBody;
    double accelYBody;
    double accelZBody;

    double rollRate;
    double pitchRate;
    double yawRate;

    void Default()
    {
        accelXBody = 0.0;
        accelYBody = 0.0;
        accelZBody = 0.0;

        rollRate = 0.0;
        pitchRate = 0.0;
        yawRate = 0.0;
    }

    ImuData &operator=(const ImuData &other)
    {
        accelXBody = other.accelXBody;
        accelYBody = other.accelYBody;
        accelZBody = other.accelZBody;

        rollRate = other.rollRate;
        pitchRate = other.pitchRate;
        yawRate = other.yawRate;

        return *this;
    }

    ImuData() : accelXBody(), accelYBody(), accelZBody(), rollRate(), pitchRate(), yawRate()
    {
        Default();
    }

    ImuData(const ImuData &other) : accelXBody(), accelYBody(), accelZBody(), rollRate(), pitchRate(), yawRate()
    {
        accelXBody = other.accelXBody;
        accelYBody = other.accelYBody;
        accelZBody = other.accelZBody;

        rollRate = other.rollRate;
        pitchRate = other.pitchRate;
        yawRate = other.yawRate;
    }
};

MESSAGE_PAYLOAD(ImuMsg, ImuData, ImuMsgId)

#endif /* F826EEC0_1BBA_4DB7_9903_1AD431D6F7E0 */
