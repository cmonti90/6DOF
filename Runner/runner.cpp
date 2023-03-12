#include "runner.h"
#include <string.h>

int main()
{
        tf = 30.0;
        counter = 0;


        char cmd[70];
        strcpy(cmd, "cd /home/cmonti/Documents/Coding/Projects/Inverted_Pendulum/Runner");
        
        int poop = system(cmd);

        if (poop == 0)
        {
                // std::cout << "The command ran with no errors!" << std::endl;
        }
        else
        {
                // std::cout << "There were errors!" << std::endl;
        }

        getSimReferences();
        getSwReferences();
        initializeSim();
        initializeSW();

        while (wrapper.pTimeMngr_->getTimeNow() <= tf)
        {
                counter++;

                if (counter % 1000 == 0)
                {
                        //printf("time = %6.3f\t", t);
                }

                runSim();
                runSW();

                if (counter % 1000 == 0)
                {
                        //std::cout << std::endl;
                }
        }

        return 1;
}

void getSimReferences()
{
        //std::cout << "pEom being given: " << wrapper.pMtr_ << std::endl;
        wrapper.pMtr_->getMotorReferences(wrapper.pTimeMngr_);
        //std::cout << std::endl;

        //std::cout << "pEom being given: " << wrapper.pMtr_ << std::endl;
        wrapper.pEom_->getEomReferences(wrapper.pTimeMngr_, wrapper.pMtr_);
        //std::cout << std::endl;

        //std::cout << "pImu being given: " << wrapper.pEom_ << std::endl;
        wrapper.pImu_->getImuReferences(wrapper.pTimeMngr_, wrapper.pEom_);
        //std::cout << std::endl;

        //std::cout << "pEnc being given: " << wrapper.pEom_ << std::endl;
        wrapper.pEnc_->getEncoderReferences(wrapper.pTimeMngr_, wrapper.pEom_);
        //std::cout << std::endl;
}

void getSwReferences()
{
        //std::cout << "pEom being given: " << wrapper.pMtr_ << std::endl;
        wrapper.pNav_->getNavReferences(wrapper.pTimeMngr_);
        //std::cout << std::endl;

        wrapper.pCon_->getControllerReferences(wrapper.pTimeMngr_, wrapper.pNav_);
}

void initializeSim()
{
        wrapper.pTimeMngr_->initialize();
        wrapper.pMtr_->initialize();
        wrapper.pEom_->initialize();
        wrapper.pImu_->initialize();
        wrapper.pEnc_->initialize();
}

void initializeSW()
{
        wrapper.pNav_->initialize();
        wrapper.pCon_->initialize();
}

void runSim(void)
{
        wrapper.pTimeMngr_->update();
        wrapper.pMtr_->exec();
        wrapper.pEom_->exec();
        wrapper.pImu_->exec();
        wrapper.pEnc_->exec();
}

void runSW(void)
{
        double encTheta = wrapper.pEnc_->getEncThetadot();

        if (counter % 1000 == 0)
        {
                //std::cout << " encTheta = " << encTheta << "  ";
        }
        wrapper.pNav_->setEncoderOutput(encTheta);
        wrapper.pNav_->exec();
        wrapper.pCon_->exec();

        // TODO: make post SW update function for this
        wrapper.pMtr_->setControllerOutput(wrapper.pCon_->getControllerOutput());
}