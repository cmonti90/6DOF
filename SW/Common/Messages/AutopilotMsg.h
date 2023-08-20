#ifndef F15DA9AA_97B0_47B5_A143_AAB1476B4CE1
#define F15DA9AA_97B0_47B5_A143_AAB1476B4CE1

#include "Message.h"

#include "MessagePayloadTemplate.hxx"

struct AutopilotData
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

    AutopilotData& operator=( const AutopilotData& other )
    {
        for (unsigned int i{ 0u }; i < 3u; ++i)
        {
            force[i] = other.force[i];
            moment[i] = other.moment[i];
        }

        return *this;
    }

    AutopilotData() : force(), moment()
    {
        Default();
    }

    AutopilotData( const AutopilotData& other ) : force(), moment()
    {
        for (unsigned int i{ 0u }; i < 3u; ++i)
        {
            force[i] = other.force[i];
            moment[i] = other.moment[i];
        }
    }
};

MESSAGE_PAYLOAD(AutopilotMsg, AutopilotData, 20)


#endif /* F15DA9AA_97B0_47B5_A143_AAB1476B4CE1 */
