#include "ControlSurfaces.h"
#include "ControlSurfacesTypes.h"

#include "Actuator.h"

ControlSurfaces::ControlSurfaces( const double runRate, const std::string name )
    : SimLib::HwIntf( runRate, name )
    , endpoint_()
    , swInData_( new CtrlSurfTypes::InData() )
    , aileronL_( new Actuator( 0.0, 0.050, 5.0 ) )
    , aileronR_( new Actuator( 0.0, 0.050, 5.0 ) )
    , elevator_( new Actuator( 0.0, 0.050, 5.0 ) )
    , rudder_  ( new Actuator( 0.0, 0.050, 5.0 ) )
{
    aileronL_->setPID( 7469.1259, 75079.5091, 52.6578, 1735.6444 );
    aileronR_->setPID( 7469.1259, 75079.5091, 52.6578, 1735.6444 );
    elevator_->setPID( 7469.1259, 75079.5091, 52.6578, 1735.6444 );
    rudder_  ->setPID( 7469.1259, 75079.5091, 52.6578, 1735.6444 );
}

ControlSurfaces::~ControlSurfaces()
{
}

void ControlSurfaces::receiveQueueMngr( std::shared_ptr< PubSub::QueueMngr >& queueMngr )
{
    endpoint_.configure( queueMngr );
}

void ControlSurfaces::initialize()
{
    swInData_->reset();

    endpoint_.subscribe< AutopilotMsg >( *swInData_ );

    aileronL_->initialize();
    aileronR_->initialize();
    elevator_->initialize();
    rudder_  ->initialize();
}

void ControlSurfaces::update()
{
    CheckForMessages();

    aileronL_->update( swInData_->aileronCmd[0] );
    aileronR_->update( swInData_->aileronCmd[1] );
    elevator_->update( swInData_->elevatorCmd );
    rudder_  ->update( swInData_->rudderCmd );
}

void ControlSurfaces::finalize()
{
    aileronL_->finalize();
    aileronR_->finalize();
    elevator_->finalize();
    rudder_  ->finalize();
}

void ControlSurfaces::CheckForMessages()
{
    PubSub::Message_Label label;
    PubSub::MessageStatus status = endpoint_.peek( label );

    while ( status == PubSub::MessageStatus::MESSAGE_AVAILABLE )
    {
        switch ( label )
        {
            case AutopilotMsg::MESSAGE_LABEL:

                endpoint_.receive< AutopilotMsg >( *swInData_ );

                break;

            default:

                endpoint_.removeTopMessage();

                break;
        }

        status = endpoint_.peek( label );
    }
}