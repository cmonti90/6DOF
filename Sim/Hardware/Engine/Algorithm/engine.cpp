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

void engine::exec()
{

    netForceBody = 0.0;
    netMomentBody = 0.0;
}
