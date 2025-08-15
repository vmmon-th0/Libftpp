#include "message.hpp"

Message::Message(int type) : _type(type)
{
    this->_buffer << type;
}

Message::~Message()
{
}

Message::Type Message::getType() const noexcept
{
    return this->_type;
}

void Message::reset()
{
    this->_buffer.reset();
}

std::size_t Message::size() const
{
    return this->_buffer.size();
}

const std::uint8_t* Message::data() const
{
    return this->_buffer.rawData().data();
}