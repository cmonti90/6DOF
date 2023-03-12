#include "imu.h"

imu::imu() : pEom_()
{
    
}

void imu::getImuReferences(TimeMngr *refTimeMngr, eom *refEom)
{
    pTimeMngr = refTimeMngr;
    pEom_ = refEom;

    //std::cout << "IMU recieved: " << pEom_ << ", " << ref << std::endl;
}

void imu::initialize()
{
    //printf("\nTODO:\t imu::initialize(), %f\n", xb);
    xbdotdot = pEom_->getEomXbdotdot();
}

void imu::exec(void)
{
    xbdotdot = pEom_->getEomXbdotdot();
}