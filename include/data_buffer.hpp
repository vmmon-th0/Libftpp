#ifndef DATA_BUFFER_HPP
#define DATA_BUFFER_HPP

#include <cstdint>
#include <cstring>
#include <stdexcept>
#include <string>
#include <type_traits>
#include <vector>

class DataBuffer
{
    public:
        DataBuffer();
        ~DataBuffer();

        void reset();
        std::size_t size() const;

        template <typename T>
        typename std::enable_if<std::is_trivially_copyable<T>::value, DataBuffer &>::type operator<<(const T &val);

        template <typename T>
        typename std::enable_if<std::is_trivially_copyable<T>::value, DataBuffer &>::type operator>>(T &val);

        DataBuffer &operator<<(const std::string &str);
        DataBuffer &operator<<(const char *str);
        DataBuffer &operator>>(std::string &str);

        DataBuffer &operator>>(std::vector<std::uint8_t> &vec);
        DataBuffer &operator<<(const std::vector<std::uint8_t> &vec);

        const std::vector<std::uint8_t> &rawData() const noexcept;

    private:
        std::size_t _read_pos;
        std::vector<std::uint8_t> _buffer;
};

template <typename T>
typename std::enable_if<std::is_trivially_copyable<T>::value, DataBuffer &>::type DataBuffer::operator<<(const T &val)
{
    const std::uint8_t *bytes = reinterpret_cast<const std::uint8_t *>(&val);
    _buffer.insert(_buffer.end(), bytes, bytes + sizeof(T));
    return *this;
}

template <typename T>
typename std::enable_if<std::is_trivially_copyable<T>::value, DataBuffer &>::type DataBuffer::operator>>(T &val)
{
    if (_read_pos + sizeof(T) > _buffer.size())
    {
        throw std::out_of_range("Not enough data in buffer");
    }
    std::memcpy(&val, _buffer.data() + _read_pos, sizeof(T));
    _read_pos += sizeof(T);
    return *this;
}

#endif