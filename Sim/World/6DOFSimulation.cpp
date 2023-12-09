
#include "6DOFSimulation.h"

#include "AircraftEntity.h"

SixDOFSimulation::SixDOFSimulation()
    : World()
    , pAircraftEntity( new AircraftEntity( 3600 ) )
{
}

SixDOFSimulation::~SixDOFSimulation()
{
}

void SixDOFSimulation::createWorld()
{
    addEntity( pAircraftEntity.get() );
}