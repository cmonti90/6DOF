
#include "AircraftEntity.h"

#include "ProcModule.h"

#include "Engine.h"
#include "IMU.h"

#include <iostream>

AircraftEntity::AircraftEntity( const double runRate )
    : Entity            ( runRate )
    , pProc             ( new ProcModule( m_queueMngr ) )
    // , pEom              ( new eom       ( runRate ) )
    , pImu              ( new IMU       ( runRate ) )
    // , pAero             ( new ( runRate ) )
    , pEngine           ( new Engine    ( runRate ) )
    // , pEarthGram        ( new ( runRate ) )
    // , pMassProps        ( new ( runRate ) )
    // , pGravity          ( new ( runRate ) )
    // , pControlSurfaces  ( new ( runRate ) )
{
}

AircraftEntity::~AircraftEntity()
{
}

void AircraftEntity::createEntity()
{
    std::cout << "AircraftEntity::createEntity() called." << std::endl;
    addSwApp( pProc.get() );

    // addModel( pEom.get(), 0 );
    addModel( pImu.get(), 10 );
    // addModel( pAero, 20 );
    addModel( pEngine.get(), 30 );
    // addModel( pEarthGram.get(), 40 );
    // addModel( pMassProps.get(), 50 );
    // addModel( pGravity.get(), 60 );
    // addModel( pControlSurfaces.get(), 70 );
}