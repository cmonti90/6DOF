#ifndef C5832684_F6C3_407F_A203_A847DE53D94E
#define C5832684_F6C3_407F_A203_A847DE53D94E

#include "Message.h"

class test2Msg : public PubSub::Message
{
public:
    test2Msg() : Message("test2Msg"), msg2data(0.0) {}
    ~test2Msg() {}

    test2Msg(const test2Msg &other) : Message(other), msg2data(other.msg2data) {}

    test2Msg &operator=(const test2Msg &other)
    {
        Message::operator=(other);
        msg2data = other.msg2data;
        return *this;
    }

    // const PubSub::Message_Label MESSAGE_LABEL{std::string("test2Msg")};

    static const PubSub::Message_Label MESSAGE_LABEL;
    double msg2data;

    // PubSub::Message_Label getMessageLabel() const override
    // {
    //     return MESSAGE_LABEL;
    // }

    Message *clone() const override
    {
        return new test2Msg(*this);
    }

    void copy(const Message *other) override
    {
        const test2Msg *pOther = dynamic_cast<const test2Msg *>(other);

        if (pOther != nullptr)
        {
            msg2data = pOther->msg2data;
        }
    }

    double dataStructure() const
    {
        return msg2data;
    }
};

#endif /* C5832684_F6C3_407F_A203_A847DE53D94E */
