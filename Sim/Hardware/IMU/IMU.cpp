#include "IMU.h"
#include "eom.h"

#include "IMUTypes.h"

#include <math.h>
#include <iostream>

const int IMU::INTERUPT_RATE = 10;

// IMU Properties
const double IMU::ACCEL_BIAS            = 0.0;
const double IMU::GYRO_BIAS             = 0.0;
const double IMU::ACCEL_NOISE_DENSITY   = 0.0;
const double IMU::GYRO_NOISE_DENSITY    = 0.0;

IMU::IMU( const double runRate, const std::string name )
    : SimLib::HwIntf( runRate, name )
    , endpoint_      ()
    , distToCg_     ( 0.0 )
    , timeStamp_    ( 0.0 )
    , measAccel_    ( 0.0 )
    , measOmega_    ( 0.0 )
    , counter_      ( 0 )
    , swOutData_    ( new IMUTypes::OutData() )
    , pEom_         ( nullptr )
{
}

IMU::~IMU()
{
}

void IMU::receiveQueueMngr( std::shared_ptr< PubSub::QueueMngr >& queueMngr )
{
    endpoint_.configure( queueMngr );
}

void IMU::requestReferences( SimLib::ReferenceRequest& refReq )
{
    refReq.requestReference( reinterpret_cast< SimLib::Model** >( &pEom_ ), "eom" );
}

void IMU::initialize()
{

}

void IMU::update()
{
    AccelerometerMeasurement();
    GyroscopeMeasurement();

    if ( counter_ % INTERUPT_RATE == 0 )
    {
        BuildSwOutput();

        endpoint_.send< ImuMsg >( *swOutData_ );
    }

    counter_++;
}


void IMU::finalize()
{
}

void IMU::AccelerometerMeasurement()
{
    myMath::Vector3d accelEcef = pEom_->getAccelEcef();


    // trueSensedAccel_[0] = accelEcef[0] - ;

    // measAccel_[0] = trueSensedAccel_ + ACCEL_BIAS;
}

void IMU::GyroscopeMeasurement()
{
    myMath::Vector3d angRatesBody = pEom_->getAngRatesBody();

    measOmega_[0] = angRatesBody[0] + GYRO_BIAS;
    measOmega_[1] = angRatesBody[1] + GYRO_BIAS;
    measOmega_[2] = angRatesBody[2] + GYRO_BIAS;
}

void IMU::BuildSwOutput()
{
    swOutData_->measAccel = measAccel_;
    swOutData_->measOmega = measOmega_;
    swOutData_->timeStamp = timeStamp_;
}