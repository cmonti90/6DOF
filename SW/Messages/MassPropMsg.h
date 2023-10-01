#ifndef A8451F51_1CD9_49A9_B6C8_C86EEE36E4EF
#define A8451F51_1CD9_49A9_B6C8_C86EEE36E4EF

#include "MessagePayloadTemplate.hxx"

#include "Matrix.h"

struct MassPropData
{
    double mass;
    double I_raw[3][3];

    void Default()
    {
        mass = 0.0;

        for ( unsigned int i{0u}; i < 3u; i++ )
        {
            for ( unsigned int j{0u}; j < 3u; j++ )
            {
                I_raw[i][j] = 0.0;
            }
        }
    }

    MassPropData()
        : mass(),
          I_raw()
    {
        Default();
    }
};

MESSAGE_PAYLOAD ( MassPropMsg, MassPropData, MassPropMsgId )

#endif /* A8451F51_1CD9_49A9_B6C8_C86EEE36E4EF */
