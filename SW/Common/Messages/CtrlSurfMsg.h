#ifndef BCDAC3B3_41A6_4230_93D3_810E27CE0C75
#define BCDAC3B3_41A6_4230_93D3_810E27CE0C75

#include "Message.h"

#include "MessagePayloadTemplate.hxx"

struct CtrlSurfData
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

    CtrlSurfData& operator=( const CtrlSurfData& other )
    {
        for (unsigned int i{ 0u }; i < 3u; ++i)
        {
            force[i] = other.force[i];
        }

        return *this;
    }

    CtrlSurfData() : force(), moment()
    {
        Default();
    }

    CtrlSurfData( const CtrlSurfData& other ) : force(), moment()
    {
        for (unsigned int i{ 0u }; i < 3u; ++i)
        {
            force[i] = other.force[i];
        }
    }
};

MESSAGE_PAYLOAD(CtrlSurfMsg, CtrlSurfData, 30)


#endif /* BCDAC3B3_41A6_4230_93D3_810E27CE0C75 */
