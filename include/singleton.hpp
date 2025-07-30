#ifndef SINGLETON_HPP
#define SINGLETON_HPP

#include "design_patterns.hpp"

template <typename TType> class Singleton
{
    public:
        static TType *instance()
        {
            if (!_instance)
            {
                throw std::runtime_error("Singleton instance not instantiated");
            }
            return _instance;
        }

        template <typename... TArgs> static void instantiate(TArgs &&...args)
        {
            if (_instance)
            {
                throw std::runtime_error("Singleton instance already instantiated");
            }
            _instance = new TType(std::forward<TArgs>(args)...);
        }

    private:
        static TType *_instance;
};

template <typename TType> TType *Singleton<TType>::_instance = nullptr;

#endif