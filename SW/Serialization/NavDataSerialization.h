#ifndef DCD602BC_57DF_464E_B43C_4E36939BC886
#define DCD602BC_57DF_464E_B43C_4E36939BC886

#include "NavMsg.h"

#include "Decorators.h"
#include "myMathVector.h"
#include "myMathDCM.h"

struct NavDeserializedData
{
    myMath::Vector3f posEci;
    myMath::Vector3f velEci;
    myMath::Vector3f accEci;

    myMath::Vector3f posEcef;
    myMath::Vector3f velEcef;
    myMath::Vector3f accEcef;

    myMath::Vector3f eulerAngs;
    myMath::Vector3f eulerAngRates;

    myMath::DCMf bodyFromEcef;
    myMath::DCMf bodyFromNed;

    myMath::Vector3f gravityEcef;

    NavDeserializedData()
        : posEci()
        , velEci()
        , accEci()
        , posEcef()
        , velEcef()
        , accEcef()
        , eulerAngs()
        , eulerAngRates()
        , bodyFromEcef()
        , bodyFromNed()
        , gravityEcef()
    {
    }

    virtual void initialize()
    {
        posEci = 0.0f;
        velEci = 0.0f;
        accEci = 0.0f;

        posEcef = 0.0f;
        velEcef = 0.0f;
        accEcef = 0.0f;

        eulerAngs     = 0.0f;
        eulerAngRates = 0.0f;

        bodyFromNed = myMath::DCMf::Identity();

        gravityEcef = 0.0f;
    }

    virtual void reset()
    {
        initialize();
    }
};

template <>
struct PayloadDeserializer< NavData > : NavDeserializedData
{
    PayloadDeserializer() : NavDeserializedData()
    {
    }

    void deserialize( const NavData& payload )
    {
        posEci = payload.posEci_raw;
        velEci = payload.velEci_raw;
        accEci = payload.accEci_raw;

        posEcef = payload.posEcef_raw;
        velEcef = payload.velEcef_raw;
        accEcef = payload.accEcef_raw;

        eulerAngs     = payload.eulerAngs_raw;
        eulerAngRates = payload.eulerAngRates_raw;

        bodyFromEcef = payload.bodyFromEcef_raw;
        bodyFromNed  = payload.bodyFromNed_raw;

        gravityEcef = payload.gravityEcef_raw;
    }
};

template <>
struct PayloadSerializer< NavData > : NavDeserializedData
{
    PayloadSerializer() : NavDeserializedData()
    {
    }

    void serialize( NavData& payload ) const
    {
        for ( unsigned int i{0u}; i < 3u; i++ )
        {
            payload.posEci_raw[i] = posEci[i];
            payload.velEci_raw[i] = velEci[i];
            payload.accEci_raw[i] = accEci[i];

            payload.posEcef_raw[i] = posEcef[i];
            payload.velEcef_raw[i] = velEcef[i];
            payload.accEcef_raw[i] = accEcef[i];

            payload.eulerAngs_raw[i] = eulerAngs[i];
            payload.eulerAngRates_raw[i] = eulerAngRates[i];

            payload.gravityEcef_raw[i] = gravityEcef[i];

            for ( unsigned int j{0u}; j < 3u; j++ )
            {
                payload.bodyFromEcef_raw[i][j] = bodyFromEcef[i][j];
                payload.bodyFromNed_raw[i][j]  = bodyFromNed[i][j];
            }
        }
    }
};

#endif /* DCD602BC_57DF_464E_B43C_4E36939BC886 */
