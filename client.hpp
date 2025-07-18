#ifndef CLIENT_HPP
#define CLIENT_HPP

#include "network.hpp"
#include "message.hpp"

class Client
{
    public:
        Client();
        ~Client();

        void connect(const std::string& address, const size_t& port);

        void disconnect();
        void defineAction(Message::Type messageType, const std::function<void(const Message&)>& action);

        void send(const Message& message);

        void update();

    private:
        int _sockfd;
        std::unordered_map<Message::Type, std::function<void(const Message&)>> _actions;
};

#endif