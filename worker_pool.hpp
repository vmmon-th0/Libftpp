#ifndef WORKER_POOL_HPP
#define WORKER_POOL_HPP

#include "threading.hpp"
#include "thread_safe_queue.hpp"

class WorkerPool
{
    public:
        class IJob
        {
            public:
                virtual ~IJob() = default;
                virtual void execute() = 0;
        };

        explicit WorkerPool(std::size_t nbThreads = std::thread::hardware_concurrency());
        ~WorkerPool();

        void addJob(const std::function<void()>& jobToExecute);
        void addJob(std::unique_ptr<IJob> job);

    private:
        void workerLoop();
        bool _stopFlag = false;
        std::mutex _mutex;
        std::condition_variable _shutdownCondition;
        ThreadSafeQueue<std::function<void()>> _jobQueue;
        std::vector<std::thread> _workers;
};

#endif