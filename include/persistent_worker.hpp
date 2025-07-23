#ifndef PERSISTENT_WORKER_HPP
#define PERSISTENT_WORKER_HPP

#include "threading.hpp"

class PersistentWorker
{
    public:
        PersistentWorker();
        ~PersistentWorker();

        void addTask(const std::string& name, const std::function<void()>& jobToExecute);
        void removeTask(const std::string& name);
        
        PersistentWorker(const PersistentWorker&) = delete;
        PersistentWorker& operator=(const PersistentWorker&) = delete;

    private:
        void _persistentLoop();
        std::mutex _mutex;
        std::thread _workerThread;
        std::atomic<bool> _running;
        std::condition_variable _cv;
        std::unordered_map<std::string, std::function<void()>> _tasks;
};

#endif