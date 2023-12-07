#ifndef D371EC60_186D_4D70_822D_DF924C522279
#define D371EC60_186D_4D70_822D_DF924C522279

#include "Entity.h"

class AircraftEntity : public Entity
{
  public:
    AircraftEntity( const double runRate );
    virtual ~AircraftEntity();

    virtual void initialize() override;
};

#endif /* D371EC60_186D_4D70_822D_DF924C522279 */
