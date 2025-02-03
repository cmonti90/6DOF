
#include "AircraftEntity.h"

#include "ProcModule.h"

#include "Aero.h"
#include "ControlSurfaces.h"
// #include "EarthGRAM.h"
#include "Engine.h"
#include "eom.h"
#include "IMU.h"
#include "MassProperties.h"

#include <iostream>

AircraftEntity::AircraftEntity( const double runRate )
    : Entity            ( runRate )
    , pProc             ( new ProcModule        ( m_queueMngr ) )
    , pEom              ( new eom               ( runRate ) )
    , pImu              ( new IMU               ( runRate ) )
    , pAero             ( new Aero              ( runRate ) )
    , pEngine           ( new Engine            ( runRate ) )
    // , pEarthGram        ( new EarthGRAM         ( runRate ) )
    , pMassProps        ( new MassProperties    ( runRate ) )
    , pControlSurfaces  ( new ControlSurfaces   ( runRate ) )
{
}

AircraftEntity::~AircraftEntity()
{
}

void AircraftEntity::createEntity()
{
    addSwApps();
    addModels();
}

void AircraftEntity::addSwApps()
{
    addSwApp( pProc.get() );
}

void AircraftEntity::addModels()
{
    addModel( pControlSurfaces.get(), 0  );
    addModel( pEngine         .get(), 10 );
    addModel( pEom            .get(), 20 );
    // addModel( pEarthGram      .get(), 30 );
    addModel( pMassProps      .get(), 40 );
    addModel( pAero           .get(), 50 );
    addModel( pImu            .get(), 60 );
}