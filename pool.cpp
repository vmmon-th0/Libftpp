#include "pool.hpp"

Pool::Pool() {};

template<typename TArgs, typename ... TArgs>
Pool::Pool::Object<class TType> acquire(Targs&& p_args)
{
}

Pool::resize(const size_t& numberOfObjectStored)
{
}

template<class TType>
TType* Pool::Object<TType>::operator->() {
    return this->ptr;
}