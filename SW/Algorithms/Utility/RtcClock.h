#ifndef B2DA04E2_7467_4411_AD9A_29B6DCE0F8C9
#define B2DA04E2_7467_4411_AD9A_29B6DCE0F8C9

#include "Time.h"

namespace TimePt
{
    class RtcClock
    {
    public:
        RtcClock() = delete;
        RtcClock(const PubSub::Time& realClock) : realClock_(realClock) {}
        virtual ~RtcClock();

        double getTimeNow(void) const
        {
            return realClock_.getTimeNow();
        }

    private:
        PubSub::Time realClock_;
    };
}

#endif /* B2DA04E2_7467_4411_AD9A_29B6DCE0F8C9 */
