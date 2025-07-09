#ifndef OBSERVER_HPP
#define OBSERVER_HPP

#include "data_structures.hpp"

template<typename TEvent>
class Observer
{
    public:
        void subscribe(const TEvent& event, const std::function<void()>& callback)
        {
            this->_callbacks[event].push_back(callback);
        }

        void notify(const TEvent& event)
        {
            auto it = this->_callbacks.find(event);
            if (it == this->_callbacks.end())
            {
                return;
            }
            auto eventCallbacks = it->second;
            for (const auto& callback : eventCallbacks)
            {
                callback();
            }
        }

    private:
        std::unordered_map<TEvent, std::vector<std::function<void()>>> _callbacks;
};

#endif