#ifndef D9E6A0CB_3DA1_4BA9_A51B_80A2E9FD2C7B
#define D9E6A0CB_3DA1_4BA9_A51B_80A2E9FD2C7B

#include "MessagePayloadTemplate.hxx"

#include "MsgIds.hpp"

struct GRAMData
{
    double density;
    double pressure;
    double temperature;

    double ewWind;
    double nsWind;
    double vertWind;

    double speedOfSound;

    void Default()
    {
        density = 0.0;
        pressure = 0.0;
        temperature = 0.0;

        ewWind = 0.0;
        nsWind = 0.0;
        vertWind = 0.0;

        speedOfSound = 0.0;
    }

    GRAMData()
    : density()
    , pressure()
    , temperature()
    , ewWind()
    , nsWind()
    , vertWind()
    , speedOfSound()
    {
        Default();
    }
};

MESSAGE_PAYLOAD( GRAMMsg, GRAMData, GRAMMsgId )

#endif /* D9E6A0CB_3DA1_4BA9_A51B_80A2E9FD2C7B */
