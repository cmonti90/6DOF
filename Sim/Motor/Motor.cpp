#include "Motor.h"
#include <random>

void Motor::getMotorReferences(TimeMngr *ref)
{
    pTimeMngr = ref;
}

Motor::Motor()
{
    
}

void Motor::initialize()
{
    //printf("\nTODO:\t Motor::intialize(), check = %i\n", check++);
    //printf("\nTODO:\t Motor::intialize(), check = %i\n", check++);
}

void Motor::exec()
{
    unsigned int seed{9};
    double dec_prec = 1e-9;

    srand(seed);
    // printf("rand = %f\n", (rand() % static_cast<unsigned int>(1.0 / dec_prec)) * dec_prec);

    omegadot = 0.0;
}