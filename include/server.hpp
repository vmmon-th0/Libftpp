#ifndef SERVER_HPP
#define SERVER_HPP

#include "message.hpp"
#include <arpa/inet.h>
#include <cstdint>
#include <cstring>
#include <errno.h>
#include <fcntl.h>
#include <functional>
#include <iostream>
#include <list>
#include <memory>
#include <sys/epoll.h>
#include <sys/socket.h>
#include <system_error>
#include <unistd.h>
#include <unordered_map>

class Server
{
    public:
        Server();
        ~Server();

        void start(const std::size_t &p_port);
        void defineAction(const Message::Type &messageType,
                          const std::function<void(long long &clientID, Message &msg)> &action);
        void sendTo(const Message &message, long long clientID);
        void sendToArray(const Message &message, std::vector<long long> clientIDs);
        void sendToAll(const Message &message);
        void update();
        uint16_t read_le16(const std::vector<std::byte> &buffer);

    private:
        int _sockfd;
        long long _clientIdCounter;

        std::unordered_map<int, std::list<Message>> _messagePool;
        std::unordered_map<long long, int> _clientIds;
        std::unordered_map<int, long long> _clientIdsReverse;
        std::unordered_map<Message::Type, std::function<void(long long &, Message &)>> _actions;
};

#endif
