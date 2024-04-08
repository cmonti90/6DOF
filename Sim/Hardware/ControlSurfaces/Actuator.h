#ifndef AED62BC2_E07D_42C8_A7C5_EFB39DB3F087
#define AED62BC2_E07D_42C8_A7C5_EFB39DB3F087

#include "myMath.h"

struct PID
{
    double p;
    double i;
    double d;
    double filterCoef;

    PID()  = default;
    ~PID() = default;
};

class Actuator
{
  public:
    Actuator();
    Actuator( const myMath::Vector3d& initAngDeflStates, const double inert = 0.0, const double damping = 0.0 );
    virtual ~Actuator();

    void initialize();
    void update( const double cmd );
    void finalize();

    void setPID( const double p, const double i, const double d, const double filterCoef );
    void setIaxis( const double inert );
    void setDampingCoeff( const double damping );

    double getDeflection() const;
    double getControllerCmd() const;

  protected:
    void Controller();
    double stateDynamics( const double cmd, const double thetaDot );
    void RungeKutta4thOrder( const double cmd );

    double Iaxis;
    double dampingCoeff;
    myMath::Vector3d angDeflStates;

    double stateErr;
    double stateErr_prev;
    double stateErr_prev2;

    PID pid;
    double integrativeError;

    double PIDcmd;
    double PIDcmd_prev;
    double PIDcmd_prev2;

  private:
    Actuator( const Actuator& )             = delete;
    Actuator& operator=( const Actuator& )  = delete;
};

#endif /* AED62BC2_E07D_42C8_A7C5_EFB39DB3F087 */
