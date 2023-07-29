#ifndef __NETWORK_HPP__
#define __NETWORK_HPP__

#include "../../bits/API.hpp"

class __network {
    private:
        int                     socket;
        fd_set                  fds;
        struct timeval          timeout;
        struct sockaddr_in      serv_addr;
        __server                server;
        std::vector<__client>   client;

    public:
        __network();
        ~__network();

        int                     get_Socket();
        fd_set                  get_fds();
        struct timeval          get_timeout();
        struct sockaddr_in      get_serv_addr();
        __server                get_server();
        std::vector<__client>   get_client();

        void                    set_Socket(int Socket);
        void                    set_fds(fd_set fds);
        void                    set_timeout(struct timeval timeout);
        void                    set_serv_addr(struct sockaddr_in serv_addr);
        void                    set_server(__server server);
        void                    set_client(std::vector<__client> client);

        void    _insert(); // set all network infos
};

#endif