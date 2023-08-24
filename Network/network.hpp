#ifndef __NETWORK_HPP__
#define __NETWORK_HPP__

#include "../Server/server.hpp"
#include "../bits/stdc++.hpp"


class __network {
    private:
        int                     sock;
        __server                server;

    public:
        __network(int &line_count, std::ifstream &configfile);
        ~__network();

        int                     get_Socket();
        __server                get_server();

        void                    set_Socket(int Socket);
        void                    set_server(__server server);

        void    Insert(); // set all network infos
        
        // this is me iharile
        void    CreateSocket(void); // create socket for each port
        int     accept_new_client(int fd);
};

#endif