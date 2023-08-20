#ifndef E379D5A1_B7C3_46B7_9DE5_37D4C17FF27D
#define E379D5A1_B7C3_46B7_9DE5_37D4C17FF27D

#include "Message.h"

#include "MessagePayloadTemplate.hxx"

struct AeroData
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

    AeroData& operator=( const AeroData& other )
    {
        for (unsigned int i{ 0u }; i < 3u; ++i)
        {
            force[i] = other.force[i];
            moment[i] = other.moment[i];
        }

        return *this;
    }

    AeroData() : force(), moment()
    {
        Default();
    }

    AeroData( const AeroData& other ) : force(), moment()
    {
        for (unsigned int i{ 0u }; i < 3u; ++i)
        {
            force[i] = other.force[i];
            moment[i] = other.moment[i];
        }
    }
};

MESSAGE_PAYLOAD(AeroMsg, AeroData, 10)

#endif /* E379D5A1_B7C3_46B7_9DE5_37D4C17FF27D */
