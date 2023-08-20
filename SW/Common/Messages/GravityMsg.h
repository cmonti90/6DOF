#ifndef A9459157_330F_44B7_8744_E91039735134
#define A9459157_330F_44B7_8744_E91039735134

#include "Message.h"

#include "MessagePayloadTemplate.hxx"

struct GravityData
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

    GravityData& operator=( const GravityData& other )
    {
        for (unsigned int i{ 0u }; i < 3u; ++i)
        {
            force[i] = other.force[i];
        }

        return *this;
    }

    GravityData() : force(), moment()
    {
        Default();
    }

    GravityData( const GravityData& other ) : force(), moment()
    {
        for (unsigned int i{ 0u }; i < 3u; ++i)
        {
            force[i] = other.force[i];
        }
    }
};

MESSAGE_PAYLOAD(GravityMsg, GravityData, 60)

#endif /* A9459157_330F_44B7_8744_E91039735134 */
