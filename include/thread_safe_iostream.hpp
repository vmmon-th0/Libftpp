#ifndef THREAD_SAFE_IOSTREAM_HPP
#define THREAD_SAFE_IOSTREAM_HPP

#include <algorithm>
#include <iostream>
#include <mutex>
#include <sstream>

// A thread-safe iostream wrapper that allows setting a prefix for each thread.
// each thread has its own instance of ThreadSafeIostream, but they share a mutex to
// ensure that output to std::cout is synchronized.

class ThreadSafeIostream
{
    public:
        ThreadSafeIostream() = default;
        ~ThreadSafeIostream() = default;

        template <typename T> void prompt(const std::string &question, T &dest)
        {
            std::lock_guard<std::mutex> lock(this->_mutex);
            std::cout << _prefix << question << std::endl;
            std::cout <<  "> ";
            std::cin >> dest;
        }

        template <typename T> ThreadSafeIostream &operator<<(const T &val)
        {
            _buffer << val;
            return *this;
        }

        void setPrefix(const std::string &prefix);
        ThreadSafeIostream &operator<<(std::ostream &(*manip)(std::ostream &));

    private:
        std::ostringstream _buffer;
        static std::mutex _mutex;
        static thread_local std::string _prefix;
};

extern thread_local ThreadSafeIostream threadSafeCout;

#endif