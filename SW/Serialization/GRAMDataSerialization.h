#ifndef C1BD515D_1B39_46BA_B708_C8C2506DDAF8
#define C1BD515D_1B39_46BA_B708_C8C2506DDAF8

#include "GRAMMsg.h"

#include "Decorators.h"
#include "Vector.h"

struct GRAMDataSerialized
{
    GRAMDataSerialized() : windNed(0.0)
    {
    }

    virtual void initialize()
    {
        windNed = 0.0;
    }

    virtual void reset()
    {
        initialize();
    }

    myMath::Vector3d windNed;
};

template <>
struct PayloadSerializer<GRAMData> : GRAMDataSerialized
{
    PayloadSerializer() : GRAMDataSerialized()
    {
    }

    void serialize(GRAMData &payload) const
    {
            payload.nsWind = windNed[0];
            payload.ewWind = windNed[1];
            payload.vertWind = -windNed[2];
    }
};

template <>
struct PayloadDeserializer<GRAMData> : GRAMDataSerialized
{
    PayloadDeserializer() : GRAMDataSerialized()
    {
    }

    void deserialize(const GRAMData &payload)
    {
        windNed[0] = payload.nsWind;
        windNed[1] = payload.ewWind;
        windNed[2] = -payload.vertWind;
    }
};


#endif /* C1BD515D_1B39_46BA_B708_C8C2506DDAF8 */
