#include "thread_safe_iostream.hpp"

thread_local ThreadSafeIostream threadSafeCout;
thread_local std::string ThreadSafeIostream::_prefix = "";
std::mutex ThreadSafeIostream::_mutex;

ThreadSafeIostream::ThreadSafeIostream() = default;
ThreadSafeIostream::~ThreadSafeIostream() = default;

void ThreadSafeIostream::setPrefix(const std::string& prefix)
{
    this->_prefix = prefix;
}

ThreadSafeIostream& ThreadSafeIostream::operator<<(std::ostream& (*manip)(std::ostream&))
{
    if (manip == static_cast<std::ostream& (*)(std::ostream&)>(std::endl))
    {
        std::lock_guard<std::mutex> lock(this->_mutex);
        std::cout << this->_prefix << _buffer.str() << std::endl;
        _buffer.str("");
        _buffer.clear();
    }
    return *this;
}