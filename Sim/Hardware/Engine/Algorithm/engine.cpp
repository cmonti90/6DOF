#include "engine.h"

#include "PhysicalProperties.h"

#include <math.h>

engine::engine()
{
}

engine::~engine()
{
}

void engine::initialize()
{
}

void engine::finalize()
{
}

void engine::exec( const EngineTypes::InData& inData, EngineTypes::OutData& outData )
{
    netForceBody  = 0.0;
    netMomentBody = 0.0;

    BuildOutput( outData );
}

void engine::BuildOutput( EngineTypes::OutData& outData )
{
    outData.forceBody = netForceBody;
    outData.momentBody = netMomentBody;
}