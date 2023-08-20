#ifndef B2DA04E2_7467_4411_AD9A_29B6DCE0F8C9
#define B2DA04E2_7467_4411_AD9A_29B6DCE0F8C9

#include "Time.h"

#include <memory>

namespace TimePt
{
    class RtcClock
    {
    public:
        RtcClock() = delete;
        RtcClock(const std::shared_ptr<PubSub::Time>& realClock) : realClock_(realClock) {}
        virtual ~RtcClock() = default;

        double getTimeNow(void) const
        {
            return realClock_->getTimeNow();
        }

    private:
        std::shared_ptr<PubSub::Time> realClock_;
    };
}

#endif /* B2DA04E2_7467_4411_AD9A_29B6DCE0F8C9 */
