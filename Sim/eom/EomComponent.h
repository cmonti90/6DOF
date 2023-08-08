
#include "SimComponent.h"
#include "test1Msg.h"
#include "test2Msg.h"
#include "test3Msg.h"

class eom;

class EomComponent : public PubSub::SimComponent
{
public:
    EomComponent(std::shared_ptr<PubSub::QueueMngr> queueMngr, const PubSub::COMPONENT_LABEL name = "EomComponent");
    virtual ~EomComponent();

    void initialize(void) override;
    void update(void) override;
    void finalize(void) override;

private:
    std::unique_ptr<eom> pEom;

    std::unique_ptr<test1Msg> test1Msg_;
    std::unique_ptr<test2Msg> test2Msg_;
    std::unique_ptr<test3Msg> test3Msg_;

    unsigned int counter_;
};