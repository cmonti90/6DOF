#ifndef BCDAC3B3_41A6_4230_93D3_810E27CE0C75
#define BCDAC3B3_41A6_4230_93D3_810E27CE0C75

#include "MessagePayloadTemplate.hxx"

#include "MsgIds.hpp"

struct CtrlSurfData
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

    CtrlSurfData &operator=(const CtrlSurfData &other)
    {
        for (unsigned int i{0u}; i < 2u; ++i)
        {
            aileronDefl[i] = other.aileronDefl[i];
        }

        elevatorDefl = other.elevatorDefl;
        rudderDefl = other.rudderDefl;

        return *this;
    }

    CtrlSurfData() : aileronDefl(), elevatorDefl(), rudderDefl()
    {
        Default();
    }

    CtrlSurfData(const CtrlSurfData &other) : aileronDefl(), elevatorDefl(), rudderDefl()
    {
        for (unsigned int i{0u}; i < 2u; ++i)
        {
            aileronDefl[i] = other.aileronDefl[i];
        }

        elevatorDefl = other.elevatorDefl;
        rudderDefl = other.rudderDefl;
    }
};

MESSAGE_PAYLOAD(CtrlSurfMsg, CtrlSurfData, CtrlSurfMsgId)

#endif /* BCDAC3B3_41A6_4230_93D3_810E27CE0C75 */
