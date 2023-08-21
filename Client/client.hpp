#ifndef __CLIENT_HPP__
#define __CLIENT_HPP__

#include "../bits/stdc++.hpp"
#include "../Request/request.hpp"
#include "../Response/response.hpp"
#include "../Server/server.hpp"
#include "../Info/info.hpp"

class __request;
class __response;

class __client {
    private:
        int                 socket;
        __server            *server;
        __request           *request;
        __response          *response;

    public:
        __client(int sock, __server *server);
        ~__client();

        size_t              get_socket();
        __server            get_server();

        void                set_server(__server *server);

        short                 Receive();
        short                 Send();
};

#endif