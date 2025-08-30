#include "data_buffer.hpp"

DataBuffer::DataBuffer() : _read_pos(0)
{
}

DataBuffer::~DataBuffer() = default;

void DataBuffer::reset() noexcept
{
    this->_read_pos = 0;
    this->_buffer = {};
}

std::size_t DataBuffer::size() const noexcept
{
    return this->_buffer.size();
}

std::size_t DataBuffer::remaining() const noexcept
{
    return this->_buffer.size() - this->_read_pos;
}

const std::vector<std::byte> &DataBuffer::rawData() const noexcept
{
    return this->_buffer;
}

DataBuffer &DataBuffer::operator<<(const std::vector<std::byte> &vec)
{
    if (vec.size() > MAX_SERIAL_SIZE)
    {
        throw std::length_error("String size exceeds maximum limit");
    }
    *this << static_cast<std::uint32_t>(vec.size());
    _buffer.insert(_buffer.end(), vec.begin(), vec.end());
    return *this;
}

DataBuffer &DataBuffer::operator<<(const std::string &str)
{
    if (str.size() > MAX_SERIAL_SIZE)
    {
        throw std::length_error("String size exceeds maximum limit");
    }
    *this << static_cast<std::uint32_t>(str.size());
    _buffer.insert(_buffer.end(),
               reinterpret_cast<const std::byte*>(str.data()),
               reinterpret_cast<const std::byte*>(str.data()) + str.size());
    return *this;
}

DataBuffer &DataBuffer::operator>>(std::vector<std::byte> &vec)
{
    std::uint32_t size = 0;
    *this >> size;
    if (_read_pos + size > _buffer.size())
    {
        throw std::out_of_range("Not enough data in buffer");
    }
    vec.resize(size);
    std::memcpy(vec.data(), _buffer.data() + _read_pos, size);
    _read_pos += size;
    return *this;
}

DataBuffer &DataBuffer::operator>>(std::string &str)
{
    std::uint32_t size = 0;
    *this >> size;
    if (_read_pos + size > _buffer.size())
    {
        throw std::out_of_range("Not enough data in buffer");
    }
    str.resize(size);
    std::memcpy(str.data(), _buffer.data() + _read_pos, size);
    _read_pos += size;
    return *this;
}