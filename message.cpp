#include "message.hpp"

Message::Message(int type): _type(type)
{
}

Message::~Message()
{
}

int Message::type()
{
    return this->_type;
}