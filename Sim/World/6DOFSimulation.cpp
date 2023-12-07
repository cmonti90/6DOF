
#include "6DOFSimulation.h"

#include "AircraftEntity.h"

SixDOFSimulation::SixDOFSimulation( const double runRate )
    : World( runRate )
    , pAircraftEntity( new AircraftEntity( runRate ) )
{
}

SixDOFSimulation::~SixDOFSimulation()
{
}

void SixDOFSimulation::createWorld()
{
    addEntity( pAircraftEntity );
}