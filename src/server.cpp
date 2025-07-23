#include "server.hpp"

Server::Server()
{
}

Server::~Server()
{
}

/* are :: necessary here ? */

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

                epoll_event cev;
                cev.events = EPOLLIN | EPOLLET;
                cev.data.fd = connFd;
                epoll_ctl(epfd, EPOLL_CTL_ADD, connFd, &cev);
            }
            else if (events[i].events & EPOLLIN)
            {
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