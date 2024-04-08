#ifndef IMU_H
#define IMU_H

#include "HwIntf.h"

#include "myMathVector.h"
#include "PayloadEndpoint.h"

class eom;

namespace IMUTypes
{
    struct OutData;
}

// Base off TDK InvenSense IIM-46230 IMU

class IMU : public SimLib::HwIntf
{
  public:
    IMU( const double runRate,
         const std::string name = "IMU" );
    ~IMU();

  protected:

    // Rate to Send Message to SW
    static const int INTERUPT_RATE;

    // IMU Properties
    static const double ACCEL_BIAS;
    static const double GYRO_BIAS;
    static const double ACCEL_NOISE_DENSITY;
    static const double GYRO_NOISE_DENSITY;

    void initialize() override;
    void update() override;
    void finalize() override;
    virtual void requestReferences( SimLib::ReferenceRequest& refReq ) override;

    void AccelerometerMeasurement();
    void GyroscopeMeasurement();
    void BuildSwOutput();

    PubSub::PayloadEndpoint endpoint_;

    const myMath::Vector3d distToCg_;
    double timeStamp_;
    
    myMath::Vector3d trueSensedAccel_;
    myMath::Vector3d measAccel_;
    myMath::Vector3d measOmega_;

    uint64_t counter_;

    std::unique_ptr< IMUTypes::OutData > swOutData_;

  private:

    eom* pEom_;

    virtual void receiveQueueMngr( std::shared_ptr< PubSub::QueueMngr >& queueMngr ) override;

    IMU( const IMU& ) = delete;
    IMU& operator=( const IMU& ) = delete;
};

#endif /* IMU_H */