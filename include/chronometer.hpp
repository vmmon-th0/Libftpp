#ifndef CHRONOMETER_HPP
#define CHRONOMETER_HPP

#include <chrono>

class ChronoMeter
{
    public:
        ChronoMeter() : _running(false)
        {
        }
        ~ChronoMeter();

        void start();
        void stop();
        void reset();
        double elapsedMilliseconds() const;
        double elapsedSeconds() const;

    private:
        bool _running;
        std::chrono::steady_clock::time_point _begin;
        std::chrono::steady_clock::time_point _end;
        std::chrono::steady_clock::duration _accum = std::chrono::steady_clock::duration::zero();
};

#endif