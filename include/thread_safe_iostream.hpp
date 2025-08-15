#ifndef THREAD_SAFE_IOSTREAM_HPP
#define THREAD_SAFE_IOSTREAM_HPP

#include <mutex>
#include <sstream>
#include <iostream>
#include <algorithm>

class ThreadSafeIostream
{
    public:
        ThreadSafeIostream();
        ~ThreadSafeIostream();

        template <typename T> void prompt(const std::string &question, T &dest)
        {
            std::lock_guard<std::mutex> lock(this->_mutex);
            std::cout << _prefix << question;
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