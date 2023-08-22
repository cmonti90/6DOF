#ifndef A8451F51_1CD9_49A9_B6C8_C86EEE36E4EF
#define A8451F51_1CD9_49A9_B6C8_C86EEE36E4EF

#include "MessagePayloadTemplate.hxx"

#include "Matrix.h"

struct MassPropData
{
    double mass;
    myMath::Matrix3d I;

    void Default()
    {
        mass = 0.0;
        I = 0.0;
    }

    MassPropData &operator=(const MassPropData &other)
    {
        mass = other.mass;
        I = other.I;

        return *this;
    }

    MassPropData()
    : mass(),
    I()
    {
        Default();
    }

    MassPropData(const MassPropData &other)
        : mass(other.mass), 
        I(other.I)
    {
    }
};

MESSAGE_PAYLOAD(MassPropMsg, MassPropData, MassPropMsgId)

#endif /* A8451F51_1CD9_49A9_B6C8_C86EEE36E4EF */
