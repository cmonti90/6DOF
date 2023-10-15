#ifndef AED62BC2_E07D_42C8_A7C5_EFB39DB3F087
#define AED62BC2_E07D_42C8_A7C5_EFB39DB3F087

#include "mathlib.h"

struct PID
{
    double p;
    double i;
    double d;

    PID()  = default;
    ~PID() = default;
};

class Actuation
{
  public:
    Actuation();
    Actuation( const myMath::Vector3d& initAngDeflStates, const double inert = 0.0, const double damping = 0.0 );
    virtual ~Actuation();

    void initialize();
    void update( double cmd );
    void finalize();

    void setPID( double p, double i, double d );
    void setIaxis( double inert );
    void setDampingCoeff( double damping );

    double getDeflection() const;

  protected:
    double controller();
    void stateDynamics( double cmd );

    double Iaxis;
    double dampingCoeff;
    myMath::Vector3d angDeflStates;

    double stateErr;
    double stateErr_prev;

    PID pid;
    double integrativeError;



  private:
    Actuation( const Actuation& )             = delete;
    Actuation& operator=( const Actuation& )  = delete;
};

#endif /* AED62BC2_E07D_42C8_A7C5_EFB39DB3F087 */
