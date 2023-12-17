#ifndef MASSPROPERTIES_H
#define MASSPROPERTIES_H

#include "Model.h"

#include "Matrix.h"

class Engine;

class MassProperties : public SimLib::Model
{
  public:
    MassProperties( const double runRate, const std::string name = "MassProperties" );
    virtual ~MassProperties();

    // Getters
    double getMass() const
    {
        return mass_;
    }

    myMath::Matrix3d getRotInertia() const
    {
        return rotInertia_;
    }

  protected:

    void initialize();
    void update();
    void finalize();

    virtual void requestReferences( SimLib::ReferenceRequest& refReq ) override;

  private:

    double mass_;
    myMath::Matrix3d rotInertia_;

    Engine* pEng_;
};

#endif /* MASSPROPERTIES_H */