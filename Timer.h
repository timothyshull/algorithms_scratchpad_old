#ifndef CH_2_1_TIMER_H
#define CH_2_1_TIMER_H

#include <chrono>

class Timer {
private:
    std::chrono::system_clock::time_point started_at;
public:
    Timer() : started_at{std::chrono::system_clock::time_point::min()} {}

    void reset() {
        started_at = std::chrono::system_clock::time_point::min();
    }

    bool is_running() const {
        return started_at.time_since_epoch() != std::chrono::system_clock::duration(0);
    }

    void start_timer() {
        started_at = std::chrono::system_clock::now();
    }

    unsigned long get_elapsed_millis() {
        if (is_running()) {
            std::chrono::system_clock::duration diff;
            diff = std::chrono::system_clock::now() - started_at;
            return static_cast<unsigned long>(diff.count());
        }
        return 0;
    }
};

#endif //CH_2_1_TIMER_H
