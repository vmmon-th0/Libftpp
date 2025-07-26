#include "server.hpp"

Server::Server(): _sockfd(-1)
{
}

Server::~Server()
{
    /* add clean shutdown, add some signal intercepter at start server */
}

void Server::start(const std::size_t& p_port)
{
    this->_sockfd = ::socket(AF_INET, SOCK_STREAM, 0);
    if (this->_sockfd < 0)
    {
        perror("socket"); // or perror ?
        return ; // throw exception lor ?
    }
    int opt = 1;
    ::setsockopt(this->_sockfd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));

    sockaddr_in addr;
    std::memset(&addr, 0, sizeof(addr));
    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = INADDR_ANY;
    addr.sin_port = htons(p_port);
    if (::bind(this->_sockfd, (sockaddr*)&addr, sizeof(addr)) < 0)
    {
        perror("bind");
        ::close(this->_sockfd);
        return ;
    }

    int flags = fcntl(this->_sockfd, F_GETFL, 0);
    if (flags == -1)
    {
        return ; // exception perhaps
    }
    ::fcntl(this->_sockfd, F_SETFL, flags | O_NONBLOCK);

    if (listen(this->_sockfd, 10) < 0)
    {
        perror("listen");
        ::close(this->_sockfd);
        return ;
    }

    int epfd = epoll_create1(0); // member attribute ?
    if (epfd < 0)
    {
        perror("listen");
        ::close(this->_sockfd);
        return ;
    }

    epoll_event ev;
    ev.events = EPOLLIN;
    ev.data.fd = this->_sockfd;
    epoll_ctl(epfd, EPOLL_CTL_ADD, this->_sockfd, &ev);

    std::vector<epoll_event> events(16);
    char buf[512];

    std::cout << "Server started on port " << p_port << "\n";

    while (true)
    {
        int n = epoll_wait(epfd, events.data(), events.size(), -1);
        if (n < 0)
        {
            perror("epoll_wait");
            break;
        }

        for (int i = 0; i < n; i++)
        {
            int fd = events[i].data.fd;

            if (fd == this->_sockfd)
            {
                sockaddr_in clientAddr;
                socklen_t clientLen = sizeof(clientAddr);
                int connFd = accept(this->_sockfd, (sockaddr*)&clientAddr, &clientLen);
                if (connFd < 0)
                {
                    perror("accept"); // perror("accept");
                    continue;
                }

                int flags = fcntl(connFd, F_GETFL, 0);
                if (flags == -1)
                {
                    return ; // exception perhaps
                }
                ::fcntl(connFd, F_SETFL, flags | O_NONBLOCK);
                this->_clientIds[++this->_clientIdCounter] = connFd;

                epoll_event cev;
                cev.events = EPOLLIN | EPOLLET;
                cev.data.fd = connFd;
                epoll_ctl(epfd, EPOLL_CTL_ADD, connFd, &cev);
            }
            else if (events[i].events & EPOLLIN)
            {
                /* integrate update here */
                while (true)
                {
                    ssize_t count = read(fd, buf, sizeof(buf));
                    if (count == -1)
                    {
                        break;
                    }
                    else if (count == 0)
                    {
                        close(fd);
                        break;
                    }
                    else
                    {
                        write(fd, buf, count);
                    }
                }
            }
        }
    }
}

void Server::defineAction(const Message::Type& messageType, const std::function<void(long long& clientID, const Message& msg)>& action)
{
    this->_actions[messageType] = action;
}

void Server::sendTo(const Message& message, long long clientID)
{
    std::size_t messageLength = message.size();
    ssize_t bytesSent = send(this->_clientIds[clientID], message.data(), sizeof(messageLength), 0);

    if (bytesSent == 0)
    {
        std::cerr << "send: connection closed by peer" << std::endl;
    }
    if (bytesSent == -1)
    {
        throw std::system_error(errno, std::generic_category(), "send failed");
    }
    std::cout << "successfully sent: " <<  bytesSent << "bytes to client: " << clientID << std::endl;
}

void Server::sendToArray(const Message& message, std::vector<long long> clientIDs)
{
    for (auto clientId: clientIDs)
    {
        this->sendTo(message, clientId);
    }
}

void Server::sendToAll(const Message& message)
{
    for (auto const[key, value]: this->_clientIds)
    {
        this->sendTo(message, key);
    }
}

/* read little‑endian 16 bits */
uint16_t read_le16(const std::vector<uint8_t>& buf)
{
    return static_cast<uint16_t>(buf[0]) | (static_cast<uint16_t>(buf[1]) << 8);
}

void Server::update()
{
}