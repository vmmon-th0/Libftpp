#ifndef CLIENT_HPP
#define CLIENT_HPP

#include "message.hpp"
#include <arpa/inet.h>
#include <cstdint>
#include <fcntl.h>
#include <functional>
#include <list>
#include <sys/socket.h>
#include <unistd.h>
#include <unordered_map>

class Client
{
    public:
        Client();
        ~Client();

        void connect(const std::string &address, const size_t &port);
        void disconnect();
        void defineAction(Message::Type messageType, const std::function<void(const Message &)> &action);
        void send(const Message &message);
        void update();

    private:
        int _sockfd;
        std::unordered_map<int, std::list<Message>> _messagePool;
        std::unordered_map<Message::Type, std::function<void(const Message &)>> _actions;
};

#endif