#include "worker_pool.hpp"

WorkerPool::WorkerPool(size_t numThreads)
{
    this->_workers.reserve(numThreads);
    for (size_t i = 0; i < numThreads; ++i)
    {
        this->_workers.emplace_back(&WorkerPool::workerLoop, this);
    }
}

WorkerPool::~WorkerPool()
{
    {
        std::lock_guard<std::mutex> lock(this->_mutex);
        this->_stopFlag = true;
    }
    this->_shutdownCondition.notify_all();
    
    for (auto& worker : this->_workers)
    {
        if (worker.joinable()) worker.join();
    }
}

void WorkerPool::addJob(const std::function<void()>& jobToExecute)
{
    std::lock_guard<std::mutex> lock(this->_mutex);
    if (this->_stopFlag)
    {
        throw std::runtime_error("Cannot add job to stopped WorkerPool");
    }
    this->_jobQueue.push_back(jobToExecute);
    this->_shutdownCondition.notify_one();
}

void WorkerPool::addJob(std::unique_ptr<IJob> job)
{
    addJob([capturedJob = std::move(job)]() mutable {
        capturedJob->execute();
    });
}

void WorkerPool::workerLoop()
{
    while (true) {
        std::unique_lock<std::mutex> lock(this->_mutex);
        this->_shutdownCondition.wait(lock, [this] {
            return !this->_jobQueue.empty() || this->_stopFlag;
        });

        if (this->_stopFlag && this->_jobQueue.empty())
        {
            return;
        }

        lock.unlock();
        std::function<void()> job;
        try
        {
            job = this->_jobQueue.pop_front();
        }
        catch (const std::runtime_error& e)
        {
            continue;
        }

        try
        {
            job();
        }
        catch (...)
        {
        }
    }
}