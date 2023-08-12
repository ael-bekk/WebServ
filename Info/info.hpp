#ifndef __INFO_HPP__
#define __INFO_HPP__

#include "../bits/stdc++.hpp"
#include "../WebServ/Network/network.hpp"
#include "../WebServ/Network/Client/client.hpp"

class __network;
class __client;

class __info
{
    private:
        int                         _max;
        std::map<int, bool>         server_sockets;
        std::map<int, bool>         client_sockets;
        std::map<int, __network *>  networks;
        std::map<int, __client *>   clients;

    private: __info();
    public: static __info& Instance();

    public:
        void update_sock(int fd);
        void add_server_sock(int fd);
        void add_network(int fd, __network & net);
        void add_client_sock(int fd);
        void add_client(int fd, __client & cnt);

        int         max_sock();
        bool        is_server_sock(int fd);
        __network&  network(int fd);
        bool        is_client_sock(int fd);
        __client&   client(int fd);

};

__info& Global();

#endif