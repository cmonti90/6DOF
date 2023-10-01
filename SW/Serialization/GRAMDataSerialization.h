#ifndef C1BD515D_1B39_46BA_B708_C8C2506DDAF8
#define C1BD515D_1B39_46BA_B708_C8C2506DDAF8

#include "GRAMMsg.h"

#include "Decorators.h"
#include "Vector.h"

template <>
struct PayloadSerializer<GRAMData>
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

    void serialize(GRAMData &payload) const
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
struct PayloadDeserializer<GRAMData>
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

    void deserialize(const GRAMData &payload)
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


#endif /* C1BD515D_1B39_46BA_B708_C8C2506DDAF8 */
