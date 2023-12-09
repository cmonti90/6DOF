#ifndef D371EC60_186D_4D70_822D_DF924C522279
#define D371EC60_186D_4D70_822D_DF924C522279

#include "Entity.h"

#include <memory>

// Forward declare SW Apps
class ProcModule;

// Forward declare Models/HwIntfs
class eom;
class IMU;
// class Aero;
class Engine;
// class EarthGRAM;
// class MassProps;
// class Gravity;
// class ControlSurfaces;



class AircraftEntity : public SimLib::Entity
{
  public:

    AircraftEntity( const double runRate );
    virtual ~AircraftEntity();

    virtual void createEntity() override;

  private:

    // SW Apps
    std::unique_ptr< ProcModule > pProc;

    // Models/HwIntfs
    std::unique_ptr< eom >            pEom;
    std::unique_ptr< IMU >            pImu;
    // std::unique_ptr< Aero >           pAero;
    std::unique_ptr< Engine >         pEngine;
    // std::unique_ptr< EarthGRAM >      pEarthGram;
    // std::unique_ptr< MassProps >      pMassProps;
    // std::unique_ptr< Gravity >        pGravity;
    // std::unique_ptr< ControlSurfaces> pControlSurfaces;

};

#endif /* D371EC60_186D_4D70_822D_DF924C522279 */
