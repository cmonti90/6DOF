#include "IMU.h"
#include "eom.h"

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
    , pEom_( nullptr )
{
}

IMU::~IMU()
{
}

void IMU::receiveQueueMngr( std::shared_ptr< PubSub::QueueMngr >& queueMngr )
{
    endoint_.configure( queueMngr );
}

SimLib::ReferenceRequest IMU::requestReferences() const
{
    SimLib::ReferenceRequest refReq;

    refReq.requestReference( "eom" );

    return refReq;
}

void IMU::getReferenceRequest( SimLib::ReferenceRequest& refReq )
{
    pEom_ = reinterpret_cast< eom* >( refReq.getReference( "eom" ) );
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
    }

    std::cout << "IMU::altSeaLevel = " << pEom_->getAltitudeSeaLevel() << std::endl;

    counter_++;
}
