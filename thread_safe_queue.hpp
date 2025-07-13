#ifndef THREAD_SAFE_QUEUE_HPP
#define THREAD_SAFE_QUEUE_HPP

#include "threading.hpp"

template <typename TType>
class ThreadSafeQueue
{
    public:
        void push_back(const TType& newElement)
        {
            std::lock_guard<std::mutex> lock(this->_mutex);
            _deque.push_back(newElement);
        }
        
        void push_front(const TType& newElement)
        {
            std::lock_guard<std::mutex> lock(this->_mutex);
            _deque.push_front(newElement);
        }
        
        TType pop_back()
        {
            std::lock_guard<std::mutex> lock(this->_mutex);
            return _deque.pop_back(newElement);
        }
        
        TType pop_front()
        {
            std::lock_guard<std::mutex> lock(this->_mutex);
            return _deque.pop_front(newElement);
        }

        bool empty()
        {
            std::lock_guard<std::mutex> lock(_mutex);
            return this->_deque.empty();
        }

    private:
        std::mutex _mutex;
        std::deque<TType> _deque;
};

#endif