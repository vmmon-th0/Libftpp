#ifndef WORKER_POOL_HPP
#define WORKER_POOL_HPP

#include "thread_safe_queue.hpp"
#include <condition_variable>
#include <thread>
#include <vector>

class WorkerPool
{
    public:
        explicit WorkerPool(std::size_t nbThreads = std::thread::hardware_concurrency());
        ~WorkerPool();

        void addJob(const std::function<void()> &jobToExecute);

    private:
        void _workerLoop();
        bool _stopFlag = false;
        
        std::mutex _mutex;
        std::condition_variable _shutdownCondition;
        ThreadSafeQueue<std::function<void()>> _jobQueue;
        std::vector<std::thread> _workers;
};

#endif