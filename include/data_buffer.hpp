#ifndef DATA_BUFFER_HPP
#define DATA_BUFFER_HPP

#include <bit>
#include <cstddef>
#include <cstdint>
#include <cstring>
#include <stdexcept>
#include <string>
#include <type_traits>
#include <vector>
#include <utility>
#include <limits>
#include <algorithm>

// Todo -> Implement C++23 move semantics and concepts

// DataBuffer is a polymorphic container for storing objects in byte format with length-prefixed encoding.
// It supports serialization and deserialization of std::is_trivially_copyable supported types through operator overloading, other specified types are also specifically supported.
// The _read_pos variable keeps track of the current read position in the buffer.

constexpr std::size_t MAX_SERIAL_SIZE = 1000000; // 1 MB

class DataBuffer
{
    public:
        explicit DataBuffer();
        ~DataBuffer();

        void reset() noexcept;
        std::size_t size() const noexcept;
        std::size_t remaining() const noexcept;

        template <typename T>
        requires std::is_trivially_copyable_v<T>
        DataBuffer &operator<<(const T &val);

        template <typename T>
        requires std::is_trivially_copyable_v<T>
        DataBuffer &operator>>(T &val);

        DataBuffer &operator<<(const std::string &str);
        DataBuffer &operator>>(std::string &str);

        DataBuffer &operator>>(std::vector<std::byte> &vec);
        DataBuffer &operator<<(const std::vector<std::byte> &vec);

        const std::vector<std::byte> &rawData() const noexcept;
        std::vector<std::byte> &rawData() noexcept = delete;

    private:
        std::size_t _read_pos;
        std::vector<std::byte> _buffer;
};

template <typename T>
requires std::is_trivially_copyable_v<T>
DataBuffer& DataBuffer::operator<<(const T &val)
{
    const std::byte *bytes = reinterpret_cast<const std::byte *>(&val);
    _buffer.insert(_buffer.end(), bytes, bytes + sizeof(T));
    return *this;
}

template <typename T>
requires std::is_trivially_copyable_v<T>
DataBuffer& DataBuffer::operator>>(T &val)
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