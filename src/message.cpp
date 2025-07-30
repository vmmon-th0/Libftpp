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