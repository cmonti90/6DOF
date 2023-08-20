#ifndef B0EB4116_CB1C_4110_A642_7A06E863FA04
#define B0EB4116_CB1C_4110_A642_7A06E863FA04

#include "Message.h"

#include "MessagePayloadTemplate.hxx"

struct EngineData
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

    EngineData& operator=( const EngineData& other )
    {
        for (unsigned int i{ 0u }; i < 3u; ++i)
        {
            force[i] = other.force[i];
            moment[i] = other.moment[i];
        }

        return *this;
    }

    EngineData() : force(), moment()
    {
        Default();
    }

    EngineData( const EngineData& other ) : force(), moment()
    {
        for (unsigned int i{ 0u }; i < 3u; ++i)
        {
            force[i] = other.force[i];
            moment[i] = other.moment[i];
        }
    }
};

MESSAGE_PAYLOAD(EngineMsg, EngineData, 40)

#endif /* B0EB4116_CB1C_4110_A642_7A06E863FA04 */
