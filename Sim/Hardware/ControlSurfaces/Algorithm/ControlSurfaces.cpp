#include "ControlSurfaces.h"

#include "Actuator.h"
#include "Units.h"

CtrlSurfs::CtrlSurfs()
    : aileronL( new Actuator( 0.0, 0.050, 5.0 ) )
    , aileronR( new Actuator( 0.0, 0.050, 5.0 ) )
    , elevator( new Actuator( 0.0, 0.050, 5.0 ) )
    , rudder  ( new Actuator( 0.0, 0.050, 5.0 ) )
{
    aileronL->setPID( 7469.1259, 75079.5091, 52.6578, 1735.6444 );
    aileronR->setPID( 7469.1259, 75079.5091, 52.6578, 1735.6444 );
    elevator->setPID( 7469.1259, 75079.5091, 52.6578, 1735.6444 );
    rudder  ->setPID( 7469.1259, 75079.5091, 52.6578, 1735.6444 );
}

CtrlSurfs::~CtrlSurfs()
{
}

void CtrlSurfs::initialize()
{
    aileronL->initialize();
    aileronR->initialize();
    elevator->initialize();
    rudder  ->initialize();
}

void CtrlSurfs::finalize()
{
    aileronL->finalize();
    aileronR->finalize();
    elevator->finalize();
    rudder  ->finalize();
}

void CtrlSurfs::exec( const CtrlSurfTypes::InData& inData, CtrlSurfTypes::OutData& outData )
{
    aileronL->update( inData.aileronCmd[0] );
    aileronR->update( inData.aileronCmd[1] );
    elevator->update( inData.elevatorCmd );
    rudder  ->update( inData.rudderCmd );

    BuildOutput( outData );
}

void CtrlSurfs::BuildOutput( CtrlSurfTypes::OutData& outData )
{
    outData.aileronDefl[0]  = aileronL->getDeflection();
    outData.aileronDefl[1]  = aileronR->getDeflection();
    outData.elevatorDefl    = elevator->getDeflection();
    outData.rudderDefl      = rudder  ->getDeflection();
}