#ifndef __INFO_HPP__
#define __INFO_HPP__

#include "../bits/stdc++.hpp"
#include "../Network/network.hpp"
#include "../Client/client.hpp"

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
        std::map<int, std::map<std::string, std::string> >RequestHeader;
        std::map<int, std::map<std::string, std::string> >ResponseHeader;

    private: __info();
    public: static __info& Instance();

    public:
        void update_sock(int fd);
        void add_server_sock(int fd);
        void add_network(int fd, __network & net);
        void add_client(int fd, __server *serv);
        void rm_client(int fd);
        void add_RequestHeader(int fd, std::string key, std::string value);
        void add_ResponseHeader(int fd, std::string key, std::string value);

        int         max_sock();
        bool        is_server_sock(int fd);
        __network&  network(int fd);
        bool        is_client_sock(int fd);
        __client&   client(int fd);
        std::string get_RequestHeader(int fd, std::string key);
        std::string get_ResponseHeader(int fd, std::string key);

        void    print_header(int fd);
};

__info& Global();

#endif