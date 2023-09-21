#ifndef B80C8142_4E9B_49D3_B7A9_C00F3B3FBF3F
#define B80C8142_4E9B_49D3_B7A9_C00F3B3FBF3F

#include "MassPropMsg.h"

#include "Decorators.h"
#include "Matrix.h"

struct MassPropDeserializedData
{
    MassPropDeserializedData() : I(0.0)
    {
    }

    virtual void initialize()
    {
        I = 0.0;
    }

    virtual void reset()
    {
        initialize();
    }

    myMath::Matrix3d I;
};

template <>
struct PayloadSerializer<MassPropData> : MassPropDeserializedData
{
    PayloadSerializer() : MassPropDeserializedData()
    {
    }

    void serialize(MassPropData &payload) const
    {
        for (unsigned int i{0u}; i < 3u; i++)
        {
            for (unsigned int j{0u}; j < 3u; j++)
            {
                payload.I_raw[i][j] = I[i][j];
            }
        }
    }
};

template <>
struct PayloadDeserializer<MassPropData> : MassPropDeserializedData
{
    PayloadDeserializer() : MassPropDeserializedData()
    {
    }

    void deserialize(const MassPropData &payload)
    {
        I = payload.I_raw;
    }
};

#endif /* B80C8142_4E9B_49D3_B7A9_C00F3B3FBF3F */
