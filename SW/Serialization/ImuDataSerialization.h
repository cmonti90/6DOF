#ifndef E3F68FC7_84EF_4814_A5BC_32A0065E9518
#define E3F68FC7_84EF_4814_A5BC_32A0065E9518

#include "ImuMsg.h"

#include "Decorators.h"
#include "myMathVector.h"


struct ImuDeserializedData
{
    myMath::Vector3d measVel;
    myMath::Vector3d measAccel;
    myMath::Vector3d measOmega;

    ImuDeserializedData()
        : measVel( 0.0 )
        , measAccel( 0.0 )
        , measOmega( 0.0 )
    {
    }

    virtual void initialize()
    {
        measVel   = 0.0;
        measAccel = 0.0;
        measOmega = 0.0;
    }

    virtual void reset()
    {
        initialize();
    }
};

template <>
struct PayloadSerializer< ImuData > : ImuDeserializedData
{
    PayloadSerializer()
    : ImuDeserializedData()
    {
    }

    void serialize( ImuData& payload ) const
    {
            payload.accelXSensor_raw = measAccel[0];
            payload.accelYSensor_raw = measAccel[1];
            payload.accelZSensor_raw = measAccel[2];

            payload.yawRateSensor_raw    = measOmega[0];
            payload.pitchRateSensor_raw  = measOmega[1];
            payload.rollRateSensor_raw   = measOmega[2];
    }
};

template <>
struct PayloadDeserializer< ImuData > : ImuDeserializedData
{
    PayloadDeserializer()
    : ImuDeserializedData()
    {
    }

    void deserialize( const ImuData& payload )
    {
        measAccel[0] = payload.accelXSensor_raw;
        measAccel[1] = payload.accelYSensor_raw;
        measAccel[2] = payload.accelZSensor_raw;
        
        measOmega[0] = payload.yawRateSensor_raw;
        measOmega[1] = payload.pitchRateSensor_raw;
        measOmega[2] = payload.rollRateSensor_raw;
    }
};

#endif /* E3F68FC7_84EF_4814_A5BC_32A0065E9518 */
