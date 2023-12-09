#include "IMU.h"

#include <math.h>
#include <iostream>

IMU::IMU( const double runRate, const std::string name )
    : SimLib::HwIntf( runRate, name )
    , endoint_()
    , deltaVel_( 0.0 )
    , gyro_( 0.0 )
    , mag_( 0.0 )
    , counter_( 0 )
    , swOutData_( new IMUTypes::OutData() )
{
}

IMU::~IMU()
{
}

void IMU::receiveQueueMngr( std::shared_ptr< PubSub::QueueMngr >& queueMngr )
{
    std::cout << "IMU::receiveQueueMngr" << std::endl;

    endoint_.configure( queueMngr );
}

void IMU::initialize()
{
    
}

void IMU::finalize()
{
}

void IMU::update()
{
    if ( counter_ % 10 == 0 )
    {
        endoint_.send< ImuMsg>( *swOutData_ );

        std::cout << "Sending IMU data" << std::endl;
    }

    counter_++;
}
