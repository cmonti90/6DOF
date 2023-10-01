#ifndef CA37D996_9D8A_4B2D_BAAF_D25120BE30FC
#define CA37D996_9D8A_4B2D_BAAF_D25120BE30FC

#include "EomMsg.h"

#include "Decorators.h"
#include "Vector.h"

struct DeserializedEomData
{
    DeserializedEomData() : windVelBody( 0.0 ),
        velBody( 0.0 ),
        accelBody( 0.0 ),
        posEci( 0.0 ),
        velEci( 0.0 ),
        posEcef( 0.0 ),
        velEcef( 0.0 ),
        eulerAngs( 0.0 ),
        eulerAngRates( 0.0 ),
        bodyFromNed( 0.0 ),
        bodyFromWind( 0.0 )
    {
    }

    virtual void initialize()
    {
        windVelBody = 0.0;
        velBody = 0.0;
        accelBody = 0.0;

        posEci = 0.0;
        velEci = 0.0;

        posEcef = 0.0;
        velEcef = 0.0;

        eulerAngs = 0.0;
        eulerAngRates = 0.0;

        bodyFromNed = 0.0;
        bodyFromWind = 0.0;
    }

    virtual void reset()
    {
        initialize();
    }

    myMath::Vector3d windVelBody;
    myMath::Vector3d velBody;
    myMath::Vector3d accelBody;

    myMath::Vector3d posEci;
    myMath::Vector3d velEci;

    myMath::Vector3d posEcef;
    myMath::Vector3d velEcef;

    myMath::AngleD eulerAngs;
    myMath::Vector3d eulerAngRates;

    myMath::DCMd bodyFromNed;
    myMath::DCMd bodyFromWind;
};

template <>
struct PayloadSerializer<EomData> : DeserializedEomData
{
    PayloadSerializer() : DeserializedEomData()
    {
    }

    void serialize( EomData& payload ) const
    {
        for ( unsigned int i = 0; i < 3; i++ )
        {
            payload.windVelBody_raw[i] = windVelBody[i];
            payload.velBody_raw[i] = velBody[i];
            payload.accelBody_raw[i] = accelBody[i];

            payload.posEci_raw[i] = posEci[i];
            payload.velEci_raw[i] = velEci[i];

            payload.posEcef_raw[i] = posEcef[i];
            payload.velEcef_raw[i] = velEcef[i];

            payload.eulerAngs_raw[i] = eulerAngs[i];
            payload.eulerAngRates_raw[i] = eulerAngRates[i];

            for ( unsigned int j{0u}; j < 3u; j++ )
            {
                payload.bodyFromNed_raw[i][j] = bodyFromNed[i][j];
                payload.bodyFromWind_raw[i][j] = bodyFromWind[i][j];
            }
        }
    }
};

template <>
struct PayloadDeserializer<EomData> : DeserializedEomData
{
    PayloadDeserializer() : DeserializedEomData()
    {
    }

    void deserialize( const EomData& payload )
    {
        windVelBody = payload.windVelBody_raw;
        velBody = payload.velBody_raw;
        accelBody = payload.accelBody_raw;

        posEci = payload.posEci_raw;
        velEci = payload.velEci_raw;

        posEcef = payload.posEcef_raw;
        velEcef = payload.velEcef_raw;

        eulerAngs = payload.eulerAngs_raw;
        eulerAngRates = payload.eulerAngRates_raw;

        bodyFromNed = payload.bodyFromNed_raw;
        bodyFromWind = payload.bodyFromWind_raw;
    }
};

#endif /* CA37D996_9D8A_4B2D_BAAF_D25120BE30FC */
