#ifndef B0EB4116_CB1C_4110_A642_7A06E863FA04
#define B0EB4116_CB1C_4110_A642_7A06E863FA04

#include "Message.h"


struct EngineMsgData
{
    double force[3];
    double moment[3];

    void Default()
    {
        for (unsigned int i{ 0u }; i < 3u; ++i)
        {
            force[i] = 0.0;
            moment[i] = 0.0;
        }
    }

    EngineMsgData& operator=( const EngineMsgData& other )
    {
        for (unsigned int i{ 0u }; i < 3u; ++i)
        {
            force[i] = other.force[i];
            moment[i] = other.moment[i];
        }

        return *this;
    }

    EngineMsgData() : force(), moment()
    {
        Default();
    }

    EngineMsgData( const EngineMsgData& other ) : force(), moment()
    {
        for (unsigned int i{ 0u }; i < 3u; ++i)
        {
            force[i] = other.force[i];
            moment[i] = other.moment[i];
        }
    }
};

class EngineMsg : public PubSub::Message
{
public:
    EngineMsg() : Message("EngineMsg"), payload()
    {
        payload.Default();
    }

    ~EngineMsg() {}

    EngineMsg(const EngineMsg &other) : Message(other), payload(other.payload) {}

    EngineMsg &operator=(const EngineMsg &other)
    {
        Message::operator=(other);
        payload = other.payload;
        return *this;
    }


    static constexpr PubSub::Message_Label MESSAGE_LABEL = 20;

    PubSub::Message_Label getMessageLabel() const override
    {
        return MESSAGE_LABEL;
    }

    EngineMsgData payload;

    Message *clone() const override
    {
        return new EngineMsg(*this);
    }

    void copy(const Message *other) override
    {
        const EngineMsg *pOther = dynamic_cast<const EngineMsg *>(other);

        if (pOther != nullptr)
        {
            payload = pOther->payload;
        }
    }

    void reset()
    {
        payload.Default();
    }
};

#endif /* B0EB4116_CB1C_4110_A642_7A06E863FA04 */
