#ifndef SERVER_HPP
#define SERVER_HPP

#include "network.hpp"
#include "message.hpp"

class Server
{
    public:
        Server();
        ~Server();

        void start(const std::size_t& p_port);
        void defineAction(const Message::Type& messageType, const std::function<void(long long& clientID, const Message& msg)>& action);
        void sendTo(const Message& message, long long clientID);
        void sendToArray(const Message& message, std::vector<long long> clientIDs);
        void sendToAll(const Message& message);
        /*if message is type of login, display every connected client + send to already connected clients a new client login with sendToArray / sendToAll*/
        void update();

    private:
        int _sockfd;
        std::unordered_map<Message::Type, std::function<void(const Message&)>> _actions;
};

#endif