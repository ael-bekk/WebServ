#ifndef __NETWORK_HPP__
#define __NETWORK_HPP__

#include "../Server/server.hpp"
#include "../bits/stdc++.hpp"
#include "../Info/info.hpp"


class __network {
    private:
        std::vector<int>        sock;
        struct addrinfo         hints;
        struct addrinfo         *res;
        __server                server;

    public:
        __network(int &line_count, std::ifstream &configfile);
        ~__network();

        std::vector<int>        get_Socket();
        sockaddr_in             get_serv_addr();
        __server                get_server();

        void                    set_Socket(int Socket);
        void                    set_serv_addr(struct sockaddr_in serv_addr);
        void                    set_server(__server server);

        void    Insert(); // set all network infos
        
        // this is me iharile
        void    CreateSocket(void); // create socket for each port
        int     accept_new_client(int fd);
};

#endif