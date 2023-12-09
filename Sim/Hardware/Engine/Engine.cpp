#include "Engine.h"

#include "PhysicalProperties.h"

#include <math.h>

#include <iostream>

Engine::Engine( const double runRate, const std::string str )
    : SimLib::Model( runRate, str )
    , netForceBody_( 0.0 )
    , netMomentBody_( 0.0 )
    , counter_( 0u )
{
}

Engine::~Engine()
{
}

void Engine::initialize()
{
    counter_ = 0u;
}

void Engine::finalize()
{
}

void Engine::update()
{
    netForceBody_  = 0.0;
    netMomentBody_ = 0.0;

    counter_++;
}