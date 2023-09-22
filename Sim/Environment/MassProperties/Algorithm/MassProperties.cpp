#include "MassProperties.h"

#include <math.h>

MassProperties::MassProperties()
{
}

MassProperties::~MassProperties()
{
}

void MassProperties::initialize(void)
{

}

void MassProperties::exec(const MassPropTypes::InData &inData, MassPropTypes::OutData &outData)
{
    outData.mass = 5000.0; // kg

    outData.I[0][0] = 250.0; // kg*m^2, Ixx
    outData.I[0][1] = 50.0;   // kg*m^2, Ixy
    outData.I[0][2] = 100.0;   // kg*m^2, Ixz

    outData.I[1][0] = outData.I[0][1]; // kg*m^2, Iyx
    outData.I[1][1] = 1000.0;          // kg*m^2, Iyy
    outData.I[1][2] = 100.0;             // kg*m^2, Iyz

    outData.I[2][0] = outData.I[0][2]; // kg*m^2, Izx
    outData.I[2][1] = outData.I[1][2]; // kg*m^2, Izy
    outData.I[2][2] = 1000.0;          // kg*m^2, Izz

}

void MassProperties::finalize()
{
    // Do nothing
}