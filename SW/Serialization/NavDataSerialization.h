#ifndef DCD602BC_57DF_464E_B43C_4E36939BC886
#define DCD602BC_57DF_464E_B43C_4E36939BC886

#include "NavMsg.h"

#include "Decorators.h"
#include "Vector.h"
#include "DCM.h"

struct NavDeserializedData
{
    myMath::Vector3d posEci;
    myMath::Vector3d velEci;
    myMath::Vector3d accEci;

    myMath::Vector3d posEcef;
    myMath::Vector3d velEcef;
    myMath::Vector3d accEcef;

    myMath::Vector3d eulerAngs;
    myMath::Vector3d eulerAngRates;

    myMath::DCMd bodyFromNed;

    NavDeserializedData() : posEci(),
        velEci(),
        accEci(),
        posEcef(),
        velEcef(),
        accEcef(),
        eulerAngs(),
        eulerAngRates()
    {
    }

    virtual void initialize()
    {
        posEci = 0.0;
        velEci = 0.0;
        accEci = 0.0;

        posEcef = 0.0;
        velEcef = 0.0;
        accEcef = 0.0;

        eulerAngs = 0.0;
        eulerAngRates = 0.0;

        bodyFromNed = myMath::DCMd::Identity();
    }

    virtual void reset()
    {
        initialize();
    }
};

template <>
struct PayloadDeserializer<NavData> : NavDeserializedData
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

        eulerAngs = payload.eulerAngs_raw;
        eulerAngRates = payload.eulerAngRates_raw;
        bodyFromNed = payload.bodyFromNed_raw;
    }
};

template <>
struct PayloadSerializer<NavData> : NavDeserializedData
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

            for ( unsigned int j{0u}; j < 3u; j++ )
            {
                payload.bodyFromNed_raw[i][j] = bodyFromNed[i][j];
            }
        }
    }
};

#endif /* DCD602BC_57DF_464E_B43C_4E36939BC886 */
