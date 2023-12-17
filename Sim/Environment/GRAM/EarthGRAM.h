#ifndef C9F664FD_0B86_499E_8314_7353A41B39E9
#define C9F664FD_0B86_499E_8314_7353A41B39E9

#include "Model.h"

#include <memory>

namespace GRAM
{
    class EarthAtmosphere;
    class Position;
    class AtmosphereState;
    class EphemerisState;
}

class eom;

class EarthGRAM : public SimLib::Model
{
  public:
    EarthGRAM( const double runRate, const std::string name = "EarthGRAM" );
    virtual ~EarthGRAM();

    // Getters

  protected:


    void initialize( void ) override;
    void update( void ) override;
    void finalize( void ) override;
    virtual void requestReferences( SimLib::ReferenceRequest& refReq ) override;

    void updateGRAM();

    std::unique_ptr<GRAM::EarthAtmosphere> earthAtmosphere_;
    std::unique_ptr<GRAM::Position> position_;
    std::unique_ptr<GRAM::AtmosphereState> atmosphereState_;
    std::unique_ptr<GRAM::EphemerisState> ephemerisState_;

    unsigned int counter_;

    eom* pEom_;

  private:

};

#endif /* C9F664FD_0B86_499E_8314_7353A41B39E9 */
