#ifndef POOL_HPP
#define POOL_HPP

#include <iostream>
#include <vector>

// To learn

// https://en.cppreference.com/w/cpp/language/value_category.html
// std::construct_at and std::destroy_at
// https://en.cppreference.com/w/cpp/language/raii.html
// https://en.cppreference.com/w/cpp/memory/unique_ptr
// https://en.cppreference.com/w/cpp/utility/forward.html
// &, &&, const &

template <typename TType> class Pool
{
    public:
        Pool() = default;

        ~Pool()
        {
            for (auto ptr : _pool)
                delete ptr;
        }

        class Object
        {
            public:
                Object(TType *ptr, Pool &poolRef) : _ptr(ptr), _poolRef(poolRef)
                {
                }

                ~Object()
                {
                    _poolRef.release(_ptr);
                }

                TType *operator->()
                {
                    return _ptr;
                }

                const TType *operator->() const
                {
                    return _ptr;
                }

            private:
                TType *_ptr;
                Pool &_poolRef;
        };

        void resize(const size_t &numberOfObjectStored)
        {
            for (auto ptr : _pool)
                delete ptr;
            _pool.clear();
            _pool.reserve(numberOfObjectStored);
            for (size_t i = 0; i < numberOfObjectStored; ++i)
            {
                _pool.push_back(new TType());
            }
        }

        template <typename... TArgs> Object acquire(TArgs &&...p_args)
        {
            if (_pool.empty())
            {
                return Object(new TType(std::forward<TArgs>(p_args)...), *this);
            }
            else
            {
                TType *ptr = _pool.back();
                _pool.pop_back();
                return Object(ptr, *this);
            }
        }

    private:
        void release(TType *ptr)
        {
            _pool.push_back(ptr);
        }

        std::vector<TType *> _pool;
};

#endif