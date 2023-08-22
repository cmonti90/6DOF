#ifndef F15DA9AA_97B0_47B5_A143_AAB1476B4CE1
#define F15DA9AA_97B0_47B5_A143_AAB1476B4CE1

#include "MessagePayloadTemplate.hxx"

#include "MsgIds.hpp"

struct AutopilotData
{
    double aileronDefl[2];
    double elevatorDefl;
    double rudderDefl;

    void Default()
    {
        for (unsigned int i{0u}; i < 2u; ++i)
        {
            aileronDefl[i] = 0.0;
        }

        elevatorDefl = 0.0;
        rudderDefl = 0.0;
    }

    AutopilotData& operator=( const AutopilotData& other )
    {
        for (unsigned int i{0u}; i < 2u; ++i)
        {
            aileronDefl[i] = other.aileronDefl[i];
        }

        elevatorDefl = other.elevatorDefl;
        rudderDefl = other.rudderDefl;

        return *this;
    }

    AutopilotData() : aileronDefl(), elevatorDefl(), rudderDefl()
    {
        Default();
    }

    AutopilotData( const AutopilotData& other ) : aileronDefl(), elevatorDefl(), rudderDefl()
    {
        for (unsigned int i{0u}; i < 2u; ++i)
        {
            aileronDefl[i] = other.aileronDefl[i];
        }

        elevatorDefl = other.elevatorDefl;
        rudderDefl = other.rudderDefl;
    }
};

MESSAGE_PAYLOAD(AutopilotMsg, AutopilotData, AutopilotMsgId)


#endif /* F15DA9AA_97B0_47B5_A143_AAB1476B4CE1 */
