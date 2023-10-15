#include "ControlSurfaces.h"

#include "Actuation.h"
#include "Units.h"

CtrlSurfs::CtrlSurfs()
    : aileronL( new Actuation( 0.0, 1.8516, 11.1316 ) )
    , aileronR( new Actuation( 0.0, 1.8516, 11.1316 ) )
    , elevator( new Actuation( 0.0, 1.8516, 11.1316 ) )
    , rudder  ( new Actuation( 0.0, 1.8516, 11.1316 ) )
    , t       ( 0.0 )
    , dt      ( 0.001 )
    , fAct    ( nullptr )
    , logOutput( true )
    , sigSign( 1.0 )
{
    aileronL->setPID( 654.2698, 191.1087, 39.3151 );
    aileronR->setPID( 654.2698, 191.1087, 39.3151 );
    elevator->setPID( 654.2698, 191.1087, 39.3151 );
    rudder  ->setPID( 654.2698, 191.1087, 39.3151 );

    if ( logOutput )
    {
        fAct = fopen( "actuation.dat", "w" );
    }
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

    if ( logOutput )
    {
        fclose( fAct );
    }
}

void CtrlSurfs::exec( const CtrlSurfTypes::InData& inData, CtrlSurfTypes::OutData& outData )
{
    const double inputTest = 5.0_deg;

    if ( static_cast<int>( t / dt ) % 1000 == 0 )
    {
        sigSign *= -1.0;
    }

    aileronL->update( sigSign * inputTest );

    // aileronL->update( inData.aileronCmd[0] );
    aileronR->update( inData.aileronCmd[1] );
    elevator->update( inData.elevatorCmd );
    rudder  ->update( inData.rudderCmd );

    if ( logOutput )
    {
        fprintf( fAct, "%f,%f,%f\n", t, sigSign * inputTest, aileronL->getDeflection() );
    }

    BuildOutput( outData );

    t += dt;
}

void CtrlSurfs::BuildOutput( CtrlSurfTypes::OutData& outData )
{
    outData.aileronDefl[0]  = aileronL->getDeflection();
    outData.aileronDefl[1]  = aileronR->getDeflection();
    outData.elevatorDefl    = elevator->getDeflection();
    outData.rudderDefl      = rudder  ->getDeflection();
}