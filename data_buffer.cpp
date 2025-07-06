#include "data_buffer.hpp"

DataBuffer::DataBuffer() : _read_pos(0)
{
}

DataBuffer::~DataBuffer() = default;

void DataBuffer::reset()
{
    _buffer.clear();
    _read_pos = 0;
}

std::size_t DataBuffer::size() const
{
    return _buffer.size();
}

DataBuffer& DataBuffer::operator<<(const std::string& str)
{
    *this << str.size();
    _buffer.insert(_buffer.end(), str.begin(), str.end());
    return *this;
}

DataBuffer& DataBuffer::operator<<(const char* str)
{
    std::size_t size = std::strlen(str);
    *this << size;
    _buffer.insert(_buffer.end(), str, str + size);
    return *this;
}

DataBuffer& DataBuffer::operator>>(std::string& str)
{
    std::size_t size;
    *this >> size;
    
    if (_read_pos + size > _buffer.size())
    {
        throw std::out_of_range("Not enough data in buffer");
    }
    
    str.assign(reinterpret_cast<const char*>(_buffer.data() + _read_pos), size);
    _read_pos += size;
    return *this;
}