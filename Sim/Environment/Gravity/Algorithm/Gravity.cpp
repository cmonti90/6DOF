#include "Gravity.h"

#include <math.h>

Gravity::Gravity()
{
}

Gravity::~Gravity()
{
}

void Gravity::initialize()
{
}

void Gravity::exec(const GravityTypes::InData& inData, GravityTypes::OutData& outData)
{
    gravForceNed = inData.mass * myMath::Constants::GRAVITY_ACCEL;

    BuildOutput(inData, outData);
}

void Gravity::finalize()
{
    // Do nothing
}

void Gravity::BuildOutput(const GravityTypes::InData& inData, GravityTypes::OutData& outData)
{
    outData.forceBody = inData.bodyFromNed * gravForceNed;
}

