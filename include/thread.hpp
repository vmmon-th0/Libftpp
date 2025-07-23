#ifndef THREAD_HPP
#define THREAD_HPP

#include "threading.hpp"
#include "thread_safe_iostream.hpp"

class Thread
{
    public:
        Thread(const std::string& name, std::function<void()> funcToExecute);
        ~Thread();

        void start();
        void stop();

    private:
        std::thread _thread;
        std::string _identifier;
        std::function<void()> _task;
};

#endif