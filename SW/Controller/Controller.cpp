#include "Controller.h"

void Controller::getControllerReferences(TimeMngr *refTimeMngr, Nav *refNav)
{
    pTimeMngr = refTimeMngr;
    pNav = refNav;
}

void Controller::initialize()
{
    //printf("\nTODO:\t Controller::initialize()\n");

    cmd = 0.0;
}

void Controller::exec()
{
    getNavStates();

    controlLaw();
}

void Controller::getNavStates()
{
    // xbStates_ = pNav->getxbStates();
    // xb = xbStates_[0];
    // xbdot = xbStates_[1];
    // xbdotdot = xbStates_[2];

    // xrStates_ = pNav->getxrStates();
    // xr = xrStates_[0];
    // xrdot = xrStates_[1];
    // xrdotdot = xrStates_[2];

    // thetaStates_ = pNav->getthetaStates();
    // theta = thetaStates_[0];
    // thetadot = thetaStates_[1];
    // thetadotdot = thetaStates_[2];
}

void Controller::controlLaw()
{
    //printf("\nTODO:\t Controller::controlLaw()\n");
}