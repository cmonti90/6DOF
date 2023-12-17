#ifndef ENGINE_H
#define ENGINE_H

#include "Model.h"

#include "mathlib.h"

class Engine : public SimLib::Model
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

    void initialize( void );
    void update();
    void finalize( void );

    myMath::Vector3d netForceBody_;
    myMath::Vector3d netMomentBody_;

    unsigned int counter_;
};

#endif /* ENGINE_H */