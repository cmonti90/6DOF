#ifndef A8451F51_1CD9_49A9_B6C8_C86EEE36E4EF
#define A8451F51_1CD9_49A9_B6C8_C86EEE36E4EF

#include "Message.h"

#include "MessagePayloadTemplate.hxx"

struct MassPropData
{
    double force[3];
    double moment[3];

    void Default()
    {
        for (unsigned int i{ 0u }; i < 3u; ++i)
        {
            force[i] = 0.0;
        }
    }

    MassPropData& operator=( const MassPropData& other )
    {
        for (unsigned int i{ 0u }; i < 3u; ++i)
        {
            force[i] = other.force[i];
        }

        return *this;
    }

    MassPropData() : force(), moment()
    {
        Default();
    }

    MassPropData( const MassPropData& other ) : force(), moment()
    {
        for (unsigned int i{ 0u }; i < 3u; ++i)
        {
            force[i] = other.force[i];
        }
    }
};

MESSAGE_PAYLOAD(MassPropMsg, MassPropData, 80)


#endif /* A8451F51_1CD9_49A9_B6C8_C86EEE36E4EF */
