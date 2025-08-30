#ifndef MESSAGE_HPP
#define MESSAGE_HPP

#include "data_buffer.hpp"

class Message
{
    public:
        using Type = int;

        explicit Message(Type t);
        ~Message();

        Type getType() const noexcept;

        void reset();
        std::size_t size() const;
        const std::byte *data() const;

        template <typename T> Message &operator<<(const T &val)
        {
            _buffer << val;
            return *this;
        }

        template <typename T> Message &operator>>(T &val)
        {
            _buffer >> val;
            return *this;
        }

    private:
        Type _type;
        DataBuffer _buffer;
};

#endif