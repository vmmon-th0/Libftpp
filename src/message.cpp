#include "message.hpp"

Message::Message(Type type) : _type(type)
{
    this->_buffer << type;
}

Message::Message() : _type(0)
{
    this->_buffer << this->_type;
}

Message::~Message()
{
}

Message::Type Message::getType() const noexcept
{
    return this->_type;
}

void Message::skipType()
{
    Type type;
    *this >> type;
}

void Message::reset()
{
    this->_buffer.reset();
}

std::size_t Message::size() const
{
    return this->_buffer.size();
}

const std::byte *Message::data() const
{
    return this->_buffer.rawData().data();
}