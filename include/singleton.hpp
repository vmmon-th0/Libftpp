#ifndef SINGLETON_HPP
#define SINGLETON_HPP

template <typename TType> class Singleton
{
    public:

        // Todo -> Are these prevent correct and sufficient?
        Singleton() = delete; // Prevent instantiation of Singleton class
        ~Singleton() = delete; // Prevent deletion of Singleton class

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
        // Todo -> inline static / init nullptr ?
        static TType *_instance;
};

#endif