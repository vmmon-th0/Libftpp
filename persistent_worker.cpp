#include "persistent_worker.hpp"

PersistentWorker::PersistentWorker() : _workerThread(std::thread(PersistentWorker::_persistentLoop)), _running(true)
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

void PersistentWorker::addTask(const std::string& name, const std::function<void()>& jobToExecute)
{
    std::lock_guard<std::mutex> lock(this->_mutex);
    this->_tasks[name] = jobToExecute;
    this->_cv.notify_one();
}

void PersistentWorker::removeTask(const std::string& name)
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
                this->_cv.wait(lock, [this] { return !this->_tasks.empty() || !this->_running; });
            }

            for (const auto& task : this->_tasks)
            {
                tasksToRun.push_back(task.second);
            }
        }

        for (const auto& task : tasksToRun)
        {
            try
            {
                task();
            } catch (...)
            {
            }
        }
    }
}
