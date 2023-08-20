#ifndef DABE8334_1F6B_471B_BBDB_38B35BA70571
#define DABE8334_1F6B_471B_BBDB_38B35BA70571

#include "Message.h"

#include "MessagePayloadTemplate.hxx"

struct EomData
{
    double force[3];
    double moment[3];

    void Default()
    {
        for (unsigned int i{ 0u }; i < 3u; ++i)
        {
            force[i] = 0.0;
        }
    }

    EomData& operator=( const EomData& other )
    {
        for (unsigned int i{ 0u }; i < 3u; ++i)
        {
            force[i] = other.force[i];
        }

        return *this;
    }

    EomData() : force(), moment()
    {
        Default();
    }

    EomData( const EomData& other ) : force(), moment()
    {
        for (unsigned int i{ 0u }; i < 3u; ++i)
        {
            force[i] = other.force[i];
        }
    }
};

MESSAGE_PAYLOAD(EomMsg, EomData, 50)


#endif /* DABE8334_1F6B_471B_BBDB_38B35BA70571 */
