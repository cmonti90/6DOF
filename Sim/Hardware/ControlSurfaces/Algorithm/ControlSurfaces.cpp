#include "ControlSurfaces.h"

CtrlSurfs::CtrlSurfs()
{
}

CtrlSurfs::~CtrlSurfs()
{
}

void CtrlSurfs::initialize()
{
}

void CtrlSurfs::finalize()
{
}

void CtrlSurfs::exec(const CtrlSurfTypes::InData& inData, CtrlSurfTypes::OutData& outData)
{
    aileronDefl[0] = inData.aileronDefl[0];
    aileronDefl[1] = inData.aileronDefl[1];
    elevatorDefl = inData.elevatorDefl;
    rudderDefl = inData.rudderDefl;

    BuildOutput(outData);
}

void CtrlSurfs::BuildOutput(CtrlSurfTypes::OutData& outData)
{
    outData.aileronDefl[0] = aileronDefl[0];
    outData.aileronDefl[1] = aileronDefl[1];
    outData.elevatorDefl = elevatorDefl;
    outData.rudderDefl = rudderDefl;
}