#include "Encoder.h"

Encoder::Encoder() : pEom_()
{
    
}

void Encoder::getEncoderReferences(TimeMngr *refTimeMngr, eom *refEom)
{
    pTimeMngr = refTimeMngr;
    pEom_ = refEom;

    //std::cout << "Encoder recieved: " << pEom_ << ", " << ref << std::endl;
}

void Encoder::initialize(void)
{
    //printf("\nEncoder::initialize()\n");

    theta = pEom_->getEomTheta();
}

void Encoder::exec(void)
{
    //printf("\nEncoder exec()\n");

    theta = pEom_->getEomTheta();
}