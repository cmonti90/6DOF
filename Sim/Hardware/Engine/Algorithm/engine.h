#ifndef ENGINE_H
#define ENGINE_H

#include "EngineTypes.h"

class engine
{
public:
    engine();
    ~engine();

    void initialize(void);
    void exec(const EngineTypes::InData& inData, EngineTypes::OutData& outData);
    void finalize(void);

protected:

    myMath::Vector3d netForceBody;
    myMath::Vector3d netMomentBody;

    void BuildOutput(EngineTypes::OutData& outData);
};

#endif /* ENGINE_H */