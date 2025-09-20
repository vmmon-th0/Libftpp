#include "persistent_worker.hpp"

PersistentWorker::PersistentWorker()
    : _running(true), _workerThread(std::thread(&PersistentWorker::_persistentLoop, this))
{
}

PersistentWorker::~PersistentWorker()
{
    this->_running = false;
    this->_cv.notify_one();
    if (this->_workerThread.joinable())
    {
        this->_workerThread.join();
    }
}

void PersistentWorker::addTask(const std::string &name, const std::function<void()> &jobToExecute)
{
    std::lock_guard<std::mutex> lock(this->_mutex);
    this->_tasks[name] = jobToExecute;
    this->_cv.notify_one();
}

void PersistentWorker::removeTask(const std::string &name)
{
    std::lock_guard<std::mutex> lock(this->_mutex);
    this->_tasks.erase(name);
}

void PersistentWorker::_persistentLoop()
{
    while (this->_running)
    {
        std::vector<std::function<void()>> tasksToRun;
        {
            std::unique_lock<std::mutex> lock(this->_mutex);
            if (this->_tasks.empty())
            {
                this->_cv.wait_for(lock, std::chrono::milliseconds(5000),
                                   [this] { return !this->_tasks.empty() || !this->_running; });
            }

            for (const auto &task : this->_tasks)
            {
                tasksToRun.push_back(task.second);
            }
        }

        for (const auto &task : tasksToRun)
        {
            try
            {
                task();
                std::this_thread::sleep_for(std::chrono::milliseconds(100));
            }
            catch (...)
            {
            }
        }
    }
}
