#ifndef THREAD_HPP
#define THREAD_HPP

#include "thread_safe_iostream.hpp"
#include <functional>
#include <thread>

class Thread
{
    public:
        Thread(const std::string &name, std::function<void()> func);
        ~Thread();

        void start();
        void stop();

    private:
        std::thread _thread;
        std::string _identifier;
        std::function<void()> _task;
};

#endif