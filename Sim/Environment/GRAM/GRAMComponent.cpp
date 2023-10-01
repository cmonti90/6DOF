
#include "GRAMComponent.h"
#include "GRAMTypes.h"

#include "SpiceLoader.h"

#include <iomanip>

GRAMComponent::GRAMComponent( std::shared_ptr<PubSub::QueueMngr> queueMngr, const PubSub::Component_Label name )
    : PubSub::SimComponent  ( queueMngr, 1000, name )
    , inData_               ( new GRAMTypes::InData() )
    , outData_              ( new GRAMTypes::OutData() )
    , earthAtmosphere_      ( GRAM::EarthAtmosphere() )
    , counter_              ( 0u )
{
    GRAM::EarthInputParameters inputParameters;

    inputParameters.spicePath = "/home/cmonti/Documents/NASA_SW_Downloads/GRAM/GRAM_Suite_1.5.1/SPICE";
    inputParameters.spiceLsk = "/lsk/naif0012.tls";
    inputParameters.spicePck = "/pck/pck00011.tpc";
    inputParameters.spiceEarth = "/spk/planets/de440_GRAM.bsp";
    inputParameters.dataPath = "/home/cmonti/Documents/NASA_SW_Downloads/GRAM/GRAM_Suite_1.5.1/Earth/data";

    earthAtmosphere_.setInputParameters( inputParameters );

    bool useRRA = false;
    // earthAtmosphere_->setUseRRA( useRRA );

    // Set the start time of the trajectory
    GRAM::GramTime ttime;
    ttime.setStartTime( 2023, 3, 15, 0, 0, 0.0, GRAM::UTC, GRAM::ERT );
    earthAtmosphere_.setStartTime( ttime );

    // Set the position
    GRAM::Position position;
    position.height = 1.0; // km
    position.latitude = 22.0; // deg
    position.longitude = 48.0; // deg
    position.elapsedTime = 0.0; // sec
    earthAtmosphere_.setPosition( position );

    // Update the atmosphere data
    earthAtmosphere_.update();

    // Print the results
    GRAM::AtmosphereState atmos = earthAtmosphere_.getAtmosphereState();
    GRAM::EphemerisState ephem = earthAtmosphere_.getEphemerisState();

    std::cout << "Pressure: " << atmos.pressure << std::endl;
    std::cout << "Temperature: " << atmos.temperature << std::endl;
    std::cout << "Density: " << atmos.density << std::endl;

    std::cout << std::endl;
    std::cout << "Solar Time: " << ephem.solarTime << std::endl;
    std::cout << "Longitude of the Sun: " << std::setprecision( 9 ) << ephem.longitudeSun << std::endl;
    std::cout << std::endl;
}

GRAMComponent::~GRAMComponent()
{
}

void GRAMComponent::initialize ( void )
{
    inData_->initialize();
    outData_->initialize();

    subscribe<EomMsg>( *inData_ );
    subscribe<MassPropMsg>( *inData_ );
    counter_ = 0u;
}

void GRAMComponent::update ( void )
{
    PubSub::Message_Label label;
    PubSub::MessageStatus status = peek ( label );

    while ( status == PubSub::MessageStatus::MESSAGE_AVAILABLE )
    {
        switch ( label )
        {
            case EomMsg::MESSAGE_LABEL:
                receive<EomMsg>( *inData_ );

                break;

            case MassPropMsg::MESSAGE_LABEL:
                receive<MassPropMsg>( *inData_ );

                break;

            default:
                removeTopMessage();
                break;
        }

        status = peek( label );
    }

    inData_->reset();

    // send<GRAMMsg>( *outData_ );

    counter_++;
}

void GRAMComponent::finalize( void )
{
}