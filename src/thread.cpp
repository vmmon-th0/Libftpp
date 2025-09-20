#include "thread.hpp"

Thread::Thread(const std::string &name, std::function<void()> func) : _identifier(name), _task(func)
{
}

Thread::~Thread() noexcept
{
    if (this->_thread.joinable())
    {
        this->stop();
    }
}

void Thread::start()
{
    if (!this->_thread.joinable())
    {
        this->_thread = std::thread(this->_task);
        return;
    }
    std::ostringstream errStr;
    errStr << "Thread is already instantiated";
    throw std::runtime_error(errStr.str());
}

void Thread::join()
{
    try
    {
        this->_thread.join();
    }
    catch (const std::system_error &e)
    {
        std::ostringstream errStr;
        errStr << "Thread join failed: " << e.what();
        //throw std::runtime_error(errStr.str());
    }
}

void Thread::stop() noexcept
{
    if (this->_thread.joinable())
    {
        this->join();
    }
}