#ifndef A9459157_330F_44B7_8744_E91039735134
#define A9459157_330F_44B7_8744_E91039735134

#include "MessagePayloadTemplate.hxx"

struct GravityData
{
    double forceBody[3];

    void Default()
    {
        for (unsigned int i{ 0u }; i < 3u; ++i)
        {
            forceBody[i] = 0.0;
        }
    }

    GravityData& operator=( const GravityData& other )
    {
        for (unsigned int i{ 0u }; i < 3u; ++i)
        {
            forceBody[i] = other.forceBody[i];
        }

        return *this;
    }

    GravityData() : forceBody()
    {
        Default();
    }

    GravityData( const GravityData& other ) : forceBody()
    {
        for (unsigned int i{ 0u }; i < 3u; ++i)
        {
            forceBody[i] = other.forceBody[i];
        }
    }
};

MESSAGE_PAYLOAD(GravityMsg, GravityData, 60)

#endif /* A9459157_330F_44B7_8744_E91039735134 */
