#ifndef IMU_H
#define IMU_H

#include "HwIntf.h"

#include "IMUTypes.h"

#include "Vector.h"
#include "PayloadEndpoint.h"

class eom;

class IMU : public SimLib::HwIntf
{
  public:
    IMU( const double runRate, const std::string name = "IMU" );
    ~IMU();

    // Getters

  protected:

    PubSub::PayloadEndpoint endoint_;

    myMath::Vector3d deltaVel_;
    myMath::Vector3d gyro_;
    myMath::Vector3d mag_;

    unsigned int counter_;

    std::unique_ptr< IMUTypes::OutData > swOutData_;

  private:

    void initialize() override;
    void update() override;
    void finalize() override;

    virtual void getReferenceRequest( SimLib::ReferenceRequest& refReq ) override;

    virtual SimLib::ReferenceRequest requestReferences() const override;

    eom* pEom_;

    virtual void receiveQueueMngr( std::shared_ptr< PubSub::QueueMngr >& queueMngr ) override;

    IMU( const IMU& ) = delete;
    IMU& operator=( const IMU& ) = delete;
};

#endif /* IMU_H */