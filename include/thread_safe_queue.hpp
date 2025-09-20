#ifndef THREAD_SAFE_QUEUE_HPP
#define THREAD_SAFE_QUEUE_HPP

#include <deque>
#include <functional>
#include <mutex>
#include <system_error>

// A simple thread-safe queue implementation using std::deque and std::mutex.
// move semantics are supported for push and pop operations.
// https://isocpp.org/blog/2012/11/universal-references-in-c11-scott-meyers

// mutable mutex ? M & M rules !

template <typename TType> class ThreadSafeQueue
{
    public:
        ThreadSafeQueue() = default;
        ~ThreadSafeQueue() = default;

        template <typename U>
        void push_back(U &&newElement)
        {
            std::lock_guard<std::mutex> lock(this->_mutex);
            this->_queue.push_back(std::forward<U>(newElement));
        }

        template <typename U>
        void push_front(U &&newElement)
        {
            std::lock_guard<std::mutex> lock(this->_mutex);
            this->_queue.push_front(std::forward<U>(newElement));
        }

        TType pop_back()
        {
            std::lock_guard<std::mutex> lock(this->_mutex);
            if (this->_queue.empty())
            {
                throw std::runtime_error("Attempt to pop from empty queue (back).");
            }
            TType val = std::move(this->_queue.back());
            this->_queue.pop_back();
            return val;
        }

        TType pop_front()
        {
            std::lock_guard<std::mutex> lock(this->_mutex);
            if (this->_queue.empty())
            {
                throw std::runtime_error("Attempt to pop from empty queue (front).");
            }
            TType val = std::move(this->_queue.front());
            this->_queue.pop_front();
            return val;
        }

        bool empty() const
        {
            std::lock_guard<std::mutex> lock(this->_mutex);
            return this->_queue.empty();
        }

        std::size_t size() const
        {
            std::lock_guard<std::mutex> lock(this->_mutex);
            return this->_queue.size();
        }

    private:
        std::deque<TType> _queue;
        mutable std::mutex _mutex;
};

#endif