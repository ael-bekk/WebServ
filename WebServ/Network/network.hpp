#ifndef __NETWORK_HPP__
#define __NETWORK_HPP__

#include "../../bits/stdc++.hpp"
#include <netdb.h>      // header file for network-related functions and structures (e.g., getaddrinfo)
#include <netinet/in.h> // header file for internet protocol-related functions and structures (e.g., sockaddr_in)
#include <sys/socket.h> // header file for socket programming functions and structures (e.g., socket, bind, listen, accept)
#include <arpa/inet.h>  // header file for internet protocol-related functions (e.g., inet_addr, inet_ntoa)
#include <string.h> // for using memset
#include <unistd.h> // for using close();
#include <arpa/inet.h> // to test inet_ntoa() function 
#include "Server/server.hpp"
#include "Client/client.hpp"
#define MAX_QUEUE 2048

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