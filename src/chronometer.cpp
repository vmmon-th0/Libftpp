#include "chronometer.hpp"

ChronoMeter::ChronoMeter() : _running(false)
{
}

ChronoMeter::~ChronoMeter() = default;

void ChronoMeter::start()
{
    if (!_running)
    {
        _running = true;
        _begin = std::chrono::steady_clock::now();
    }
}

void ChronoMeter::stop()
{
    if (_running)
    {
        _end = std::chrono::steady_clock::now();
        _accum += _end - _begin;
        _running = false;
    }
}

void ChronoMeter::reset()
{
    _accum = std::chrono::steady_clock::duration::zero();
    _running = false;
}

double ChronoMeter::elapsedMilliseconds() const
{
    return std::chrono::duration<double, std::milli>(_accum).count();
}

double ChronoMeter::elapsedSeconds() const
{
    return std::chrono::duration<double>(_accum).count();
}