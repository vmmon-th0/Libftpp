#include "data_buffer.hpp"

DataBuffer::DataBuffer() : _read_pos(0)
{
}

DataBuffer::~DataBuffer() = default;

void DataBuffer::reset()
{
    this->_buffer.clear();
    _read_pos = 0;
}

std::size_t DataBuffer::size() const
{
    return this->_buffer.size();
}

const std::vector<std::uint8_t> &DataBuffer::rawData() const noexcept
{
    return this->_buffer;
}

DataBuffer &DataBuffer::operator<<(const std::vector<std::uint8_t> &vec)
{
    *this << static_cast<std::uint32_t>(vec.size());
    _buffer.insert(_buffer.end(), vec.begin(), vec.end());
    return *this;
}

DataBuffer &DataBuffer::operator>>(std::vector<std::uint8_t> &vec)
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