#ifndef MASSPROPERTIES_H
#define MASSPROPERTIES_H

#include "Model.h"

class Engine;

class MassProperties : public SimLib::Model
{
  public:
    MassProperties( const double runRate, const std::string name = "MassProperties" );
    virtual ~MassProperties();

  protected:

  private:

    void initialize();
    void update();
    void finalize();

    virtual void getReferenceRequest( SimLib::ReferenceRequest& refReq ) override;

    virtual SimLib::ReferenceRequest requestReferences() const override;

    Engine* pEng_;
};

#endif /* MASSPROPERTIES_H */