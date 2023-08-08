#ifndef BE78C0BE_F497_449B_815A_2D0E7F9278DC
#define BE78C0BE_F497_449B_815A_2D0E7F9278DC

#include "Message.h"


class test1Msg : public PubSub::Message
{
public:
    test1Msg() : Message("test1Msg"), msg1data(0.0) {}
    ~test1Msg() {}

    test1Msg(const test1Msg& other) : Message(other), msg1data(other.msg1data) {}

    test1Msg& operator=(const test1Msg& other)
    {
        Message::operator=(other);
        msg1data = other.msg1data;
        return *this;
    }

    const static PubSub::Message_Label MESSAGE_LABEL;
    double msg1data;

    Message* clone() const override
    {
        return new test1Msg(*this);
    }

    void copy(const Message* other) override
    {

        const test1Msg* pOther = dynamic_cast<const test1Msg*>(other);
        
        if (pOther != nullptr)
        {
            msg1data = pOther->msg1data;
        }
    }

    double dataStructure() const
    {
        return msg1data;
    }


};

#endif /* BE78C0BE_F497_449B_815A_2D0E7F9278DC */
