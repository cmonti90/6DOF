#ifndef F0E54CE1_F91C_4C79_AA42_F2C458B40EDB
#define F0E54CE1_F91C_4C79_AA42_F2C458B40EDB

#include "AeroMsg.h"

#include "Decorators.h"
#include "Vector.h"

template <>
struct PayloadSerializer<AeroData>
{
    PayloadSerializer() : forceBody(0.0),
                          momentBody(0.0)
    {
    }

    virtual void initialize()
    {
        forceBody = 0.0;
        momentBody = 0.0;
    }

    void serialize(AeroData &payload) const
    {
        for (unsigned int i = 0; i < 3; i++)
        {
            payload.forceBody_raw[i] = forceBody[i];
            payload.momentBody_raw[i] = momentBody[i];
        }
    }

    virtual void reset()
    {
        initialize();
    }

    myMath::Vector3d forceBody;
    myMath::Vector3d momentBody;
};

template <>
struct PayloadDeserializer<AeroData>
{
    PayloadDeserializer() : forceBody(0.0),
                            momentBody(0.0)
    {
    }

    virtual void initialize()
    {
        forceBody = 0.0;
        momentBody = 0.0;
    }

    void deserialize(const AeroData &payload)
    {
        forceBody = payload.forceBody_raw;
        momentBody = payload.momentBody_raw;
    }

    virtual void reset()
    {
        initialize();
    }

    myMath::Vector3d forceBody;
    myMath::Vector3d momentBody;
};

#endif /* F0E54CE1_F91C_4C79_AA42_F2C458B40EDB */
