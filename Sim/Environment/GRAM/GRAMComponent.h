#ifndef C9F664FD_0B86_499E_8314_7353A41B39E9
#define C9F664FD_0B86_499E_8314_7353A41B39E9

#include "SimComponent.h"

#include <memory>

namespace GRAM
{
    class EarthAtmosphere;
    class Position;
    class AtmosphereState;
    class EphemerisState;
}

namespace GRAMTypes
{
    struct InData;
    struct OutData;
}

class GRAMComponent : public PubSub::SimComponent
{
    public:
        GRAMComponent( std::shared_ptr<PubSub::QueueMngr> queueMngr, const PubSub::Component_Label name = "GRAMComponent" );
        virtual ~GRAMComponent();

        void initialize( void ) override;
        void update( void ) override;
        void finalize( void ) override;

    protected:

        std::unique_ptr<GRAMTypes::InData> inData_;
        std::unique_ptr<GRAMTypes::OutData> outData_;

        void updateGRAM();
        void BuildOutput();

    private:

        std::unique_ptr<GRAM::EarthAtmosphere> earthAtmosphere_;
        std::unique_ptr<GRAM::Position> position_;
        std::unique_ptr<GRAM::AtmosphereState> atmosphereState_;
        std::unique_ptr<GRAM::EphemerisState> ephemerisState_;

        unsigned int counter_;
};

#endif /* C9F664FD_0B86_499E_8314_7353A41B39E9 */
