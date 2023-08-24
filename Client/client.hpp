#ifndef __CLIENT_HPP__
#define __CLIENT_HPP__

#include "../bits/stdc++.hpp"
#include "../Request/request.hpp"
#include "../Response/response.hpp"
#include "../Server/server.hpp"

class __request;
class __response;
class __server;

class __client {
    private:
        std::string         host;
        std::string         port;
        int                 socket;
        __server            *server;
        __request           *request;
        __response          *response;

    public:
        __client(int sock, std::string host, std::string port, __server *server);
        ~__client();

        size_t              get_socket();
        __server            get_server();
        std::string         get_host();
        std::string         get_port();

        void                MatchLocation();
        void                set_server(__server *server);

        short               Receive();
        short               Send();
};

#endif