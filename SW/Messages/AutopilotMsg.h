#ifndef F15DA9AA_97B0_47B5_A143_AAB1476B4CE1
#define F15DA9AA_97B0_47B5_A143_AAB1476B4CE1

#include "MessagePayloadTemplate.hxx"

#include "MsgIds.hpp"

struct AutopilotData
{
    double aileronCmd[2];
    double elevatorCmd;
    double rudderCmd;

    void Default()
    {
        for (unsigned int i{0u}; i < 2u; ++i)
        {
            aileronCmd[i] = 0.0;
        }

        elevatorCmd = 0.0;
        rudderCmd = 0.0;
    }

    AutopilotData() : aileronCmd(), elevatorCmd(), rudderCmd()
    {
        Default();
    }
};

MESSAGE_PAYLOAD(AutopilotMsg, AutopilotData, AutopilotMsgId)


#endif /* F15DA9AA_97B0_47B5_A143_AAB1476B4CE1 */
