#ifndef TIMER_HPP
#define TIMER_HPP

#include <chrono>

class Timer
{
    public:
        Timer();
        ~Timer();

        void start(std::chrono::steady_clock::duration d);
        bool isTimedOut() const;
        void reset();

    private:
        std::chrono::steady_clock::duration _duration;
        std::chrono::steady_clock::time_point _start;
};

#endif