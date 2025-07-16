#ifndef MESSAGE_HPP
#define MESSAGE_HPP

#include "network.hpp"

class Message
{
    public:

        Message(int type);
        ~Message();

        int type();

    private:

        int _type;
        std::string _content;
}

#endif