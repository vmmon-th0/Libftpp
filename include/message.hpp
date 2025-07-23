#ifndef MESSAGE_HPP
#define MESSAGE_HPP

#include "network.hpp"
#include "data_buffer.hpp"

class Message
{
    public:
        using Type = int;

        explicit Message(Type t);

        Type getType() const noexcept;

        template<typename T>
        Message& operator<<(const T& val)
        {
            _buffer << val;
            return *this;
        }

        template<typename T>
        Message& operator>>(T& val)
        {
            _buffer >> val;
            return *this;
        }

        void reset()
        {
            _buffer.reset();
        }

        std::size_t size() const
        {
            return _buffer.size();
        }

        const std::uint8_t* data() const
        {
            return _buffer.rawData().data();
        }

    private:
        Type           _type;
        DataBuffer     _buffer;
};

#endif