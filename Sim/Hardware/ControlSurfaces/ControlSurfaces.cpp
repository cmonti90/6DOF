#include "ControlSurfaces.h"
#include "ControlSurfacesTypes.h"

#include "Actuator.h"

ControlSurfaces::ControlSurfaces( const double runRate, const std::string name )
    : SimLib::HwIntf( runRate, name )
    , endpoint_()
    , swInData_( new CtrlSurfTypes::InData() )
    , fin1_( new Actuator( 0.0, 0.050, 5.0 ) )
    , fin2_( new Actuator( 0.0, 0.050, 5.0 ) )
    , fin3_( new Actuator( 0.0, 0.050, 5.0 ) )
    , fin4_( new Actuator( 0.0, 0.050, 5.0 ) )
{
    fin1_->setPID( 7469.1259, 75079.5091, 52.6578, 1735.6444 );
    fin2_->setPID( 7469.1259, 75079.5091, 52.6578, 1735.6444 );
    fin3_->setPID( 7469.1259, 75079.5091, 52.6578, 1735.6444 );
    fin4_->setPID( 7469.1259, 75079.5091, 52.6578, 1735.6444 );
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

    fin1_->initialize();
    fin2_->initialize();
    fin3_->initialize();
    fin4_->initialize();
}

void ControlSurfaces::update()
{
    CheckForMessages();

    fin1_->update( swInData_->finCmd[0] );
    fin2_->update( swInData_->finCmd[1] );
    fin3_->update( swInData_->finCmd[2] );
    fin4_->update( swInData_->finCmd[3] );
}

void ControlSurfaces::finalize()
{
    fin1_->finalize();
    fin2_->finalize();
    fin3_->finalize();
    fin4_->finalize();
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


// Getters

void ControlSurfaces::GetFinDeflections( float ( &finPosOut )[4] ) const
{
    finPosOut[0] = fin1_->getDeflection();
    finPosOut[1] = fin2_->getDeflection();
    finPosOut[2] = fin3_->getDeflection();
    finPosOut[3] = fin4_->getDeflection();
}