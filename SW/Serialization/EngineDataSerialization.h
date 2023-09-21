#ifndef E3F68FC7_84EF_4814_A5BC_32A0065E9518
#define E3F68FC7_84EF_4814_A5BC_32A0065E9518

#include "EngineMsg.h"

#include "Decorators.h"
#include "Vector.h"

template <>
struct PayloadSerializer<EngineData>
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

    void serialize(EngineData &payload) const
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
struct PayloadDeserializer<EngineData>
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

    void deserialize(const EngineData &payload)
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

#endif /* E3F68FC7_84EF_4814_A5BC_32A0065E9518 */
