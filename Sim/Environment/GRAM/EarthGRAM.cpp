
#include "EarthGRAM.h"

#include "EarthAtmosphere.h"

#include "SpiceLoader.h"

#include "eom.h"

#include <iomanip>

#include "mathlib.h"

EarthGRAM::EarthGRAM( const double runRate,
                      const std::string name )
    : SimLib::Model     ( runRate, name )
    , earthAtmosphere_  ( new GRAM::EarthAtmosphere() )
    , position_         ( new GRAM::Position() )
    , atmosphereState_  ( new GRAM::AtmosphereState() )
    , ephemerisState_   ( new GRAM::EphemerisState() )
    , counter_          ( 0u )
    , pEom_             ( nullptr )
{
    GRAM::EarthInputParameters inputParameters;

    inputParameters.spicePath  = "/home/cmonti/Documents/NASA_SW/GRAM/GRAM_Suite_2.0.0/GRAM Suite 2.0/SPICE";
    inputParameters.spiceLsk   = "/lsk/naif0012.tls";
    inputParameters.spicePck   = "/pck/pck00011.tpc";
    inputParameters.spiceEarth = "/spk/planets/de440_GRAM.bsp";
    inputParameters.dataPath   = "/home/cmonti/Documents/NASA_SW/GRAM/GRAM_Suite_2.0.0/GRAM Suite 2.0/Earth/data";

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

EarthGRAM::~EarthGRAM()
{
}

void EarthGRAM::requestReferences( SimLib::ReferenceRequest& refReq )
{
    refReq.requestReference( reinterpret_cast< SimLib::Model** >( &pEom_ ), "eom" );
}

void EarthGRAM::initialize ( void )
{

    counter_ = 0u;
}

void EarthGRAM::update ( void )
{

    updateGRAM();

    counter_++;
}

void EarthGRAM::finalize( void )
{
}

void EarthGRAM::updateGRAM()
{
    // Set the position
    position_->height = 1.0 / 1000.0; // km
    position_->latitude = 45.0 * myMath::Constants::RAD_TO_DEG; // deg
    position_->longitude = 60.0 * myMath::Constants::RAD_TO_DEG; // deg
    // position->height = inData_->altGeodetic / 1000.0; // km
    // position_->latitude = inData_->lat * myMath::Constants::RAD_TO_DEG; // deg
    // position_->longitude = inData_->lon * myMath::Constants::RAD_TO_DEG; // deg
    position_->elapsedTime += 1.0 / 1000.0; // sec
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