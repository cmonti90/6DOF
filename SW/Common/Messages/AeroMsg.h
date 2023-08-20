#ifndef E379D5A1_B7C3_46B7_9DE5_37D4C17FF27D
#define E379D5A1_B7C3_46B7_9DE5_37D4C17FF27D

#include "Message.h"

struct AeroData
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

    AeroData& operator=( const AeroData& other )
    {
        for (unsigned int i{ 0u }; i < 3u; ++i)
        {
            force[i] = other.force[i];
            moment[i] = other.moment[i];
        }

        return *this;
    }

    AeroData() : force(), moment()
    {
        Default();
    }

    AeroData( const AeroData& other ) : force(), moment()
    {
        for (unsigned int i{ 0u }; i < 3u; ++i)
        {
            force[i] = other.force[i];
            moment[i] = other.moment[i];
        }
    }
};

class AeroMsg : public PubSub::Message
{
public:
    AeroMsg() : Message( "AeroMsg" ), payload()
    {
    }

    ~AeroMsg() {}

    AeroMsg( const AeroMsg& other ) : Message( other ), payload(other.payload)
    {
    }

    AeroMsg& operator=( const AeroMsg& other )
    {
        Message::operator=( other );

        payload = other.payload;

        return *this;
    }

    static constexpr PubSub::Message_Label MESSAGE_LABEL = 10;

    PubSub::Message_Label getMessageLabel() const override
    {
        return MESSAGE_LABEL;
    }

    AeroData payload;

    Message* clone() const override
    {
        return new AeroMsg( *this );
    }

    void copy( const Message* other ) override
    {
        const AeroMsg* pOther = dynamic_cast< const AeroMsg* >( other );

        if (pOther != nullptr)
        {
            payload = pOther->payload;
        }
    }

    void reset() override
    {
        payload.Default();
    }
};


#endif /* E379D5A1_B7C3_46B7_9DE5_37D4C17FF27D */
