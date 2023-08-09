#ifndef __NETWORK_HPP__
#define __NETWORK_HPP__

#include "../../bits/stdc++.hpp"

#include "Server/server.hpp"
#include "Client/client.hpp"


class __network {
    private:
        std::vector<int>        sock;
        fd_set                  r;
        fd_set                  w;
        fd_set                  readable;
        fd_set                  writable;
        struct timeval          timeout;
        struct addrinfo         hints;
        struct addrinfo         *res;
        __server                server;
        std::vector<__client>   client;

    public:
        __network(int &line_count, std::ifstream &configfile);
        ~__network();

        std::vector<int>        get_Socket();
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

        void    Insert(); // set all network infos
        
        // this is me iharile
        void    CreateSocket(void); // create socket for each port

};

#endif