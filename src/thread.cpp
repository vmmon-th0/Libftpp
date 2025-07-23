#include "thread.hpp"

Thread::Thread(const std::string& name, std::function<void()> funcToExecute): _identifier(name), _task(funcToExecute)
{
}

Thread::~Thread()
{
    /* improve err management */
    this->stop();
}

void Thread::start()
{
    if (!this->_thread.joinable())
    {
        this->_thread = std::thread(this->_task, this->_identifier);
        return ;
    }
    std::ostringstream errStr;
    errStr << "Thread id: " << this->_thread.get_id() << " is already instantiated";
    throw std::runtime_error(errStr.str());
}

void Thread::stop()
{
    if (this->_thread.joinable())
    {
        this->_thread.join();
        return ;
    }
    std::ostringstream errStr;
    errStr << "Thread id: " << this->_thread.get_id() << " is not joinable";
    throw std::runtime_error(errStr.str());
}