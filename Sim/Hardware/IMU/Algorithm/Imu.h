#ifndef IMU_H
#define IMU_H

#include "ImuTypes.h"

#include "Vector.h"

class Imu
{
public:
    Imu();
    ~Imu();

    void initialize(void);
    void exec(const ImuTypes::InData& inData, ImuTypes::OutData& outData);
    void finalize(void);

protected:
    myMath::Vector3d deltaVel;
    myMath::Vector3d gyro;
    myMath::Vector3d mag;


    void BuildOutput(ImuTypes::OutData& outData);
};

#endif /* IMU_H */