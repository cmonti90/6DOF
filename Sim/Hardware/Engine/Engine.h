#ifndef ENGINE_H
#define ENGINE_H

#include "HwIntf.h"
#include "PayloadEndpoint.h"

#include "myMath.h"

#include <memory>

namespace EngineTypes
{
    struct InData;
}

namespace SimLib
{
    class ForceEffector;
}

class Engine : public SimLib::HwIntf
{
  public:
    Engine( const double runRate, const std::string str = "Engine" );
    virtual ~Engine();

    // Getters
    myMath::Vector3d getNetForceBody( void ) const
    {
        return netForceBody_;
    }

    myMath::Vector3d getNetMomentBody( void ) const
    {
        return netMomentBody_;
    }

  protected:

    void initialize() override;
    void update() override;
    void finalize() override;
    virtual void requestReferences( SimLib::ReferenceRequest& refReq ) override;

    void CheckForMessages();

    PubSub::PayloadEndpoint endpoint_;

    std::unique_ptr< EngineTypes::InData > swInData_;

    myMath::Vector3d netForceBody_;
    myMath::Vector3d netMomentBody_;

    unsigned int counter_;

  private:

    virtual void receiveQueueMngr( std::shared_ptr< PubSub::QueueMngr >& queueMngr ) override;

    SimLib::ForceEffector* pForceEffector_;
};

#endif /* ENGINE_H */