#ifndef POOL_HPP
#define POOL_HPP

#include "data_structures.hpp"

class Pool
{
    private:

        template<class TType>
        class Object
        {
            private:
                TType* ptr;
            
            public:
                const TType* operator -> () const;
        };

        std::vector<std::unique_ptr<Pool::Object<class TType>>> objPool;

    public:

        void resize(const size_t& numberOfObjectStored);
        
        template<typename TArgs, typename ... TArgs>
        Pool::Object<class TType> acquire(TArgs&& p_args);
};

#endif