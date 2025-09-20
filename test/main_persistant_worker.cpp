#include "persistent_worker.hpp"
#include "thread_safe_iostream.hpp"
#include <iostream>

int main() {
    PersistentWorker worker;

    auto task1 = []() {
        threadSafeCout << "Executing Task 1" << std::endl;
    };

    auto task2 = []() {
        threadSafeCout << "Executing Task 2" << std::endl;
    };

    worker.addTask("Task1", task1);
    worker.addTask("Task2", task2);

    std::this_thread::sleep_for(std::chrono::seconds(1));
    
    worker.removeTask("Task1");
    
    auto tp = std::chrono::steady_clock::now();
    auto ms = std::chrono::duration_cast<std::chrono::milliseconds>(
              tp.time_since_epoch()).count();
    std::cout << "Main thread timestamp: " << ms << " ms since epoch, after removing task 1" << std::endl;
    
    std::this_thread::sleep_for(std::chrono::seconds(1));
    return 0;
}

