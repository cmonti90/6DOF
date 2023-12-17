#include "MassProperties.h"

#include "Engine.h"

#include <math.h>

MassProperties::MassProperties( const double runRate, const std::string name )
    : SimLib::Model( runRate, name )
    , mass_( 5000.0 )
    , rotInertia_( { 250.0, 50.0, 100.0, 1000.0, 100.0, 1000.0, 100.0, 1000.0, 1000.0 } )
    , pEng_( nullptr )
{
}

MassProperties::~MassProperties()
{
}

void MassProperties::requestReferences( SimLib::ReferenceRequest& refReq )
{
    refReq.requestReference( reinterpret_cast< SimLib::Model** >( &pEng_ ), "Engine" );
}

void MassProperties::initialize( void )
{

}

void MassProperties::update()
{
    /*
    outData.mass = 5000.0; // kg

    outData.I[0][0] = 250.0; // kg*m^2, Ixx
    outData.I[0][1] = 50.0;   // kg*m^2, Ixy
    outData.I[0][2] = 100.0;   // kg*m^2, Ixz

    outData.I[1][0] = outData.I[0][1]; // kg*m^2, Iyx
    outData.I[1][1] = 1000.0;          // kg*m^2, Iyy
    outData.I[1][2] = 100.0;             // kg*m^2, Iyz

    outData.I[2][0] = outData.I[0][2]; // kg*m^2, Izx
    outData.I[2][1] = outData.I[1][2]; // kg*m^2, Izy
    outData.I[2][2] = 1000.0;          // kg*m^2, Izz
    */
}

void MassProperties::finalize()
{
    // Do nothing
}