#include "ControlSurfaces.h"
#include "ControlSurfacesTypes.h"

#include "Actuator.h"

ControlSurfaces::ControlSurfaces( const double runRate, const std::string name )
    : SimLib::HwIntf( runRate, name )
    , endpoint_()
    , swInData_( new CtrlSurfTypes::InData() )
    , aileronL( new Actuator( 0.0, 0.050, 5.0 ) )
    , aileronR( new Actuator( 0.0, 0.050, 5.0 ) )
    , elevator( new Actuator( 0.0, 0.050, 5.0 ) )
    , rudder  ( new Actuator( 0.0, 0.050, 5.0 ) )
{
    aileronL->setPID( 7469.1259, 75079.5091, 52.6578, 1735.6444 );
    aileronR->setPID( 7469.1259, 75079.5091, 52.6578, 1735.6444 );
    elevator->setPID( 7469.1259, 75079.5091, 52.6578, 1735.6444 );
    rudder  ->setPID( 7469.1259, 75079.5091, 52.6578, 1735.6444 );
}

ControlSurfaces::~ControlSurfaces()
{
}

void ControlSurfaces::receiveQueueMngr( std::shared_ptr< PubSub::QueueMngr >& queueMngr )
{
    endpoint_.configure( queueMngr );
}

SimLib::ReferenceRequest ControlSurfaces::requestReferences() const
{
    SimLib::ReferenceRequest refReq;

    // refReq.requestReference( "eom" );

    return refReq;
}

void ControlSurfaces::getReferenceRequest( SimLib::ReferenceRequest& refReq )
{
    // pEom_ = reinterpret_cast< eom* >( refReq.getReference( "eom" ) );
}

void ControlSurfaces::initialize()
{
    swInData_->reset();

    endpoint_.subscribe< AutopilotMsg >( *swInData_ );

    aileronL->initialize();
    aileronR->initialize();
    elevator->initialize();
    rudder  ->initialize();
}

void ControlSurfaces::finalize()
{
    aileronL->finalize();
    aileronR->finalize();
    elevator->finalize();
    rudder  ->finalize();
}

void ControlSurfaces::update()
{
    aileronL->update( swInData_->aileronCmd[0] );
    aileronR->update( swInData_->aileronCmd[1] );
    elevator->update( swInData_->elevatorCmd );
    rudder  ->update( swInData_->rudderCmd );

}