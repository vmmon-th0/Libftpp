#include "timer.hpp"

Timer::Timer() : _duration(std::chrono::steady_clock::duration::zero()), _start(std::chrono::steady_clock::now())
{
}

Timer::~Timer() = default;

void Timer::start(std::chrono::steady_clock::duration d)
{
    this->_duration = d;
    this->_start = std::chrono::steady_clock::now();
}

bool Timer::isTimedOut() const
{
    return std::chrono::steady_clock::now() - this->_start >= this->_duration;
}

void Timer::reset()
{
    this->_start = std::chrono::steady_clock::now();
}