#include "client.hpp"

Client::Client(): _sockfd(-1)
{
}

Client::~Client()
{
    disconnect();
}

void Client::connect(const std::string& address, const size_t& port)
{
    if (this->_sockfd != -1)
    {
        throw std::runtime_error("Already connected");
    }
    this->_sockfd = ::socket(AF_INET, SOCK_STREAM, 0);
    if (this->_sockfd < 0)
    {
        throw std::runtime_error("Failed to create socket");
    }

    int flags = fcntl(this->_sockfd, F_GETFL, 0);
    fcntl(this->_sockfd, F_SETFL, flags | O_NONBLOCK);

    sockaddr_in serv_addr{};
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(static_cast<uint16_t>(port));
    if (inet_pton(AF_INET, address.c_str(), &serv_addr.sin_addr) <= 0)
    {
        ::close(this->_sockfd);
        this->_sockfd = -1;
        throw std::invalid_argument("Invalid address: " + address);
    }

    if (::connect(this->_sockfd, reinterpret_cast<sockaddr*>(&serv_addr), sizeof(serv_addr)) < 0)
    {
        if (errno != EINPROGRESS)
        {
            ::close(this->_sockfd);
            this->_sockfd = -1;
            throw std::runtime_error("Connection failed");
        }
    }
}

void Client::disconnect()
{
    if (this->_sockfd != -1)
    {
        ::close(this->_sockfd);
        this->_sockfd = -1;
    }
}

void Client::defineAction(Message::Type messageType, const std::function<void(const Message&)>& action)
{
    this->_actions[messageType] = action;
}

void Client::send(const Message& message)
{
    if (this->_sockfd < 0)
    {
        throw std::runtime_error("Not connected");
    }
    const std::uint8_t* dataPtr = message.data();

    size_t totalSent = 0;
    while (totalSent < message.size())
    {
        ssize_t sent = ::send(this->_sockfd, dataPtr + totalSent, message.size() - totalSent, 0);
        if (sent < 0 && errno != EWOULDBLOCK && errno != EAGAIN)
        {
            throw std::runtime_error("Send failed");
        }
        if (sent > 0)
        {
            totalSent += static_cast<size_t>(sent);
        }
    }
}

/* read little‑endian 16 bits */
uint16_t read_le16(const std::vector<uint8_t>& buf)
{
    return static_cast<uint16_t>(buf[0]) | (static_cast<uint16_t>(buf[1]) << 8);
}

void Client::update()
{
    if (this->_sockfd < 0)
    {
        return;
    }

    std::vector<uint8_t> buffer(4096);
    ssize_t bytesRead = ::recv(this->_sockfd, buffer.data(), buffer.size(), 0);
    while (bytesRead > 0)
    {
        std::vector<uint8_t> data(buffer.begin(), buffer.begin() + bytesRead);
        Message msg(read_le16(buffer));

        msg << buffer;

        auto it = this->_actions.find(msg.getType());
        if (it != this->_actions.end())
        {
            it->second(msg);
        }

        bytesRead = ::recv(this->_sockfd, buffer.data(), buffer.size(), 0);
    }
    // If bytesRead < 0 and errno is EWOULDBLOCK/EAGAIN, no more data now
}