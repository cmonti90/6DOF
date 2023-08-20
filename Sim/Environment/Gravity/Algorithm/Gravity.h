#ifndef GRAVITY_H
#define GRAVITY_H

#include "TimeMngr.h"
#include "mathlib.h"

class Gravity
{
protected:

public:
    Gravity();
    ~Gravity();

    void initialize(void);
    void exec(void);
    void finalize(void);

protected:

private:
    Gravity& operator=(const Gravity& orig) = delete;
    Gravity(const Gravity& orig) = delete;
};

#endif /* GRAVITY_H */