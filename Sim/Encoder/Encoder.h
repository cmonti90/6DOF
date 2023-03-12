#ifndef ENCODER_H
#define ENCODER_H

#include <iostream>
#include <array>
#include "eom.h"
#include "TimeMngr.h"

class Encoder
{
protected:
    TimeMngr *pTimeMngr;
    eom *pEom_;

    double thetadotdot{0.0};
    double thetadot{0.0};
    double theta{0.0};


public:
    Encoder();
    ~Encoder();
    Encoder(const Encoder&);
    Encoder &operator=(const Encoder &);
    void getEncoderReferences(TimeMngr *refTimeMngr, eom *refEom);
    void initialize();
    void exec(void);

    void setEomOutputs(void)
    {
        theta = pEom_->getEomTheta();
    }

    double getEncThetadot(void)
    {
        return theta;
    }

    std::array<double, 3> getthetaStates(void)
    {
        std::array<double, 3> tmp;

        tmp[0] = theta;
        tmp[1] = thetadot;
        tmp[2] = thetadotdot;

        return tmp;
    };
};

#endif