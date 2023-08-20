#ifndef IMU_H
#define IMU_H

#include "TimeMngr.h"
#include "mathlib.h"

class Imu
{
public:
    Imu();
    ~Imu();

    void initialize(void);
    void exec(void);
    void finalize(void);

protected:
    double ctrlInput;

    myMath::Vector3d netForceBody;
    myMath::Vector3d netMomentBody;
};

#endif /* IMU_H */