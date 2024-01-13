
#include "6DOFSimulation.h"

#include "AircraftEntity.h"

SixDOFSimulation::SixDOFSimulation()
    : World( SixDOFSimulation::SimulationRunRate )
    , pAircraftEntity( new AircraftEntity( static_cast< double >( SixDOFSimulation::SimulationRunRate ) ) )
{
}

SixDOFSimulation::~SixDOFSimulation()
{
}

void SixDOFSimulation::createWorld()
{
    addEntity( pAircraftEntity.get() );
}