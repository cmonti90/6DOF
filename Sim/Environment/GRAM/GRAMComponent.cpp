
#include "GRAMComponent.h"
#include "GRAMTypes.h"

#include "EarthAtmosphere.h"

#include "SpiceLoader.h"

#include <iomanip>

GRAMComponent::GRAMComponent( std::shared_ptr<PubSub::QueueMngr> queueMngr, const PubSub::Component_Label name )
    : PubSub::SimComponent  ( queueMngr, 1000, name )
    , inData_               ( new GRAMTypes::InData() )
    , outData_              ( new GRAMTypes::OutData() )
    , earthAtmosphere_      ( new GRAM::EarthAtmosphere() )
    , position_             ( new GRAM::Position() )
    , atmosphereState_      ( new GRAM::AtmosphereState() )
    , ephemerisState_       ( new GRAM::EphemerisState() )
    , counter_              ( 0u )
{
    GRAM::EarthInputParameters inputParameters;

    inputParameters.spicePath = "/home/cmonti/Documents/NASA_SW_Downloads/GRAM/GRAM_Suite_1.5.1/SPICE";
    inputParameters.spiceLsk = "/lsk/naif0012.tls";
    inputParameters.spicePck = "/pck/pck00011.tpc";
    inputParameters.spiceEarth = "/spk/planets/de440_GRAM.bsp";
    inputParameters.dataPath = "/home/cmonti/Documents/NASA_SW_Downloads/GRAM/GRAM_Suite_1.5.1/Earth/data";

    earthAtmosphere_->setInputParameters( inputParameters );

    bool useRRA = false;
    // earthAtmosphere_->setUseRRA( useRRA );

    // Set the start time of the trajectory
    GRAM::GramTime ttime;
    ttime.setStartTime( 2023, 3, 15, 0, 0, 0.0, GRAM::UTC, GRAM::ERT );
    earthAtmosphere_->setStartTime( ttime );

    // Set the position
    position_->height = 1.0; // km
    position_->latitude = 22.0; // deg
    position_->longitude = 48.0; // deg
    position_->elapsedTime = 0.0; // sec
    earthAtmosphere_->setPosition( *position_ );

    // Update the atmosphere data
    earthAtmosphere_->update();
    
}

GRAMComponent::~GRAMComponent()
{
}

void GRAMComponent::initialize ( void )
{
    inData_->initialize();
    outData_->initialize();

    subscribe<EomMsg>( *inData_ );

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

            default:
                removeTopMessage();
                break;
        }

        status = peek( label );
    }

    updateGRAM();
    BuildOutput();

    send<GRAMMsg>( *outData_ );

    inData_->reset();
    outData_->reset();
    counter_++;
}

void GRAMComponent::finalize( void )
{
}

void GRAMComponent::updateGRAM()
{
    // Set the position
    position_->height = 1.0 / 1000.0; // km
    position_->latitude = 45.0 * myMath::Constants::RAD_TO_DEG; // deg
    position_->longitude = 60.0 * myMath::Constants::RAD_TO_DEG; // deg
    // position->height = inData_->altGeodetic / 1000.0; // km
    // position_->latitude = inData_->lat * myMath::Constants::RAD_TO_DEG; // deg
    // position_->longitude = inData_->lon * myMath::Constants::RAD_TO_DEG; // deg
    position_->elapsedTime += 1.0/1000.0; // sec
    earthAtmosphere_->setPosition( *position_ );

    // Update the atmosphere data
    earthAtmosphere_->update();

    // Log states
    *atmosphereState_ = earthAtmosphere_->getAtmosphereState();
    *ephemerisState_ = earthAtmosphere_->getEphemerisState();

    // std::cout << "Pressure: " << atmos.pressure << std::endl;
    // std::cout << "Temperature: " << atmos.temperature << std::endl;
    // std::cout << "Density: " << atmos.density << std::endl;

    // std::cout << std::endl;
    // std::cout << "Solar Time: " << ephem.solarTime << std::endl;
    // std::cout << "Longitude of the Sun: " << std::setprecision( 9 ) << ephem.longitudeSun << std::endl;
    // std::cout << std::endl;
}

void GRAMComponent::BuildOutput()
{
    outData_->density = atmosphereState_->density;
    outData_->pressure = atmosphereState_->pressure;
    outData_->temperature = atmosphereState_->temperature;

    outData_->nsWind = atmosphereState_->nsWind;
    outData_->ewWind = atmosphereState_->ewWind;
    outData_->vertWind = atmosphereState_->verticalWind;
}