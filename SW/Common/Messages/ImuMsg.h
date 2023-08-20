#ifndef F826EEC0_1BBA_4DB7_9903_1AD431D6F7E0
#define F826EEC0_1BBA_4DB7_9903_1AD431D6F7E0

#include "Message.h"

#include "MessagePayloadTemplate.hxx"

struct ImuData
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

    ImuData& operator=( const ImuData& other )
    {
        for (unsigned int i{ 0u }; i < 3u; ++i)
        {
            force[i] = other.force[i];
            moment[i] = other.moment[i];
        }

        return *this;
    }

    ImuData() : force(), moment()
    {
        Default();
    }

    ImuData( const ImuData& other ) : force(), moment()
    {
        for (unsigned int i{ 0u }; i < 3u; ++i)
        {
            force[i] = other.force[i];
            moment[i] = other.moment[i];
        }
    }
};

MESSAGE_PAYLOAD(ImuMsg, ImuData, 45)


#endif /* F826EEC0_1BBA_4DB7_9903_1AD431D6F7E0 */
