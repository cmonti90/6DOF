#ifndef F826EEC0_1BBA_4DB7_9903_1AD431D6F7E0
#define F826EEC0_1BBA_4DB7_9903_1AD431D6F7E0

#include "MessagePayloadTemplate.hxx"

#include "MsgIds.hpp"

struct ImuData
{
    double velXSensor_raw;
    double velYSensor_raw;
    double velZSensor_raw;

    double accelXSensor_raw;
    double accelYSensor_raw;
    double accelZSensor_raw;

    double rollRateSensor_raw;
    double pitchRateSensor_raw;
    double yawRateSensor_raw;

    double timeStamp;

    void Default()
    {
        velXSensor_raw = 0.0;
        velYSensor_raw = 0.0;
        velZSensor_raw = 0.0;

        accelXSensor_raw = 0.0;
        accelYSensor_raw = 0.0;
        accelZSensor_raw = 0.0;

        rollRateSensor_raw  = 0.0;
        pitchRateSensor_raw = 0.0;
        yawRateSensor_raw   = 0.0;

        timeStamp = 0.0;
    }

    ImuData()
        : velXSensor_raw()
        , velYSensor_raw()
        , velZSensor_raw()
        , accelXSensor_raw()
        , accelYSensor_raw()
        , accelZSensor_raw()
        , rollRateSensor_raw()
        , pitchRateSensor_raw()
        , yawRateSensor_raw()
        , timeStamp()
    {
        Default();
    }
};

MESSAGE_PAYLOAD( ImuMsg, ImuData, ImuMsgId )

#endif /* F826EEC0_1BBA_4DB7_9903_1AD431D6F7E0 */
