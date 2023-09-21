#ifndef C6925D95_B823_4548_8C20_3D0BC8518DA2
#define C6925D95_B823_4548_8C20_3D0BC8518DA2

#include "GravityMsg.h"

#include "Decorators.h"
#include "Vector.h"

template<>
struct PayloadSerializer<GravityData>
{
    PayloadSerializer() : forceBody(0.0)
    {

    }

    virtual void initialize()
    {
        forceBody = 0.0;
    }

    void serialize(GravityData& payload) const
    {
        for (unsigned int i = 0; i < 3; i++)
        {
            payload.forceBody_raw[i] = forceBody[i];
        }
    }

    virtual void reset()
    {
        initialize();
    }

    myMath::Vector3d forceBody;
};

template<>
struct PayloadDeserializer<GravityData>
{
    PayloadDeserializer() : forceBody(0.0)
    {

    }

    virtual void initialize()
    {
        forceBody = 0.0;
    }

    void deserialize(const GravityData& payload)
    {
        forceBody = payload.forceBody_raw;
    }

    virtual void reset()
    {
        initialize();
    }

    myMath::Vector3d forceBody;
};

#endif /* C6925D95_B823_4548_8C20_3D0BC8518DA2 */
