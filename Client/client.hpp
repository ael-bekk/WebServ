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
        size_t              infile;
        size_t              outfile;
        __server            *server;
        __request           *request;
        __response          *response;

    public:
        __client(int sock, __server *server);
        ~__client();

        size_t              get_socket();
        size_t              get_infile();
        size_t              get_outfile();
        __server            get_server();

        void                set_infile(size_t infile);
        void                set_outfile(size_t outfile);
        void                set_server(__server *server);

        bool                Send();
        bool                Receive();
};

#endif