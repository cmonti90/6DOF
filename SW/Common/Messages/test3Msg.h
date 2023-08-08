#ifndef B0EB4116_CB1C_4110_A642_7A06E863FA04
#define B0EB4116_CB1C_4110_A642_7A06E863FA04

#include "Message.h"

class test3Msg : public PubSub::Message
{
public:
    test3Msg() : Message("test3Msg"), msg3data(0.0) {}
    ~test3Msg() {}

    test3Msg(const test3Msg &other) : Message(other), msg3data(other.msg3data) {}

    test3Msg &operator=(const test3Msg &other)
    {
        Message::operator=(other);
        msg3data = other.msg3data;
        return *this;
    }

    // const PubSub::Message_Label MESSAGE_LABEL{std::string("test3Msg")};

    static const PubSub::Message_Label MESSAGE_LABEL;
    double msg3data;

    // PubSub::Message_Label getMessageLabel() const override
    // {
    //     return MESSAGE_LABEL;
    // }

    Message *clone() const override
    {
        return new test3Msg(*this);
    }

    void copy(const Message *other) override
    {
        const test3Msg *pOther = dynamic_cast<const test3Msg *>(other);

        if (pOther != nullptr)
        {
            msg3data = pOther->msg3data;
        }
    }

    double dataStructure() const
    {
        return msg3data;
    }
};

#endif /* B0EB4116_CB1C_4110_A642_7A06E863FA04 */
