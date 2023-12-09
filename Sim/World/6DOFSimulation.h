#ifndef D5458C6E_153E_4D9C_92AC_AE03FDDAB884
#define D5458C6E_153E_4D9C_92AC_AE03FDDAB884

#include "World.h"

#include <memory>

class AircraftEntity;

class SixDOFSimulation : public SimLib::World
{
  public:
    SixDOFSimulation();
    virtual ~SixDOFSimulation();

    void createWorld() override;

  private:

    std::shared_ptr< AircraftEntity > pAircraftEntity;
};


#endif /* D5458C6E_153E_4D9C_92AC_AE03FDDAB884 */
