#include "runner.h"
#include <string.h>

int main()
{
        tf = 30.0;
        counter = 0;

        getSimReferences();
        initializeSim();

        while (wrapper.pTimeMngr_->getTimeNow() <= tf)
        {
                counter++;

                if (counter % 1000 == 0)
                {
                        //printf("time = %6.3f\t", t);
                }

                runSim();
        }

        return 1;
}

void getSimReferences()
{
        wrapper.pEom_->getEomReferences(wrapper.pTimeMngr_);
}

void initializeSim()
{
        wrapper.pTimeMngr_->initialize();
        wrapper.pEom_->initialize();
}

void runSim(void)
{
        wrapper.pTimeMngr_->update();
        wrapper.pEom_->exec();
}