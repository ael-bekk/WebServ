#ifndef __INFO_HPP__
#define __INFO_HPP__

#include "../bits/stdc++.hpp"
#include "../Network/network.hpp"
#include "../Client/client.hpp"

class __network;
class __client;
class __server;

typedef struct _cgi_info {
    std::string path;
    time_t      tm;
    int         status;
    int         pid;
    _cgi_info() : status(-1) { time(&this->tm); }
} _cgi_info;

class __info
{
    private:
        int                                                         _max;
        std::map<int, bool>                                         server_sockets;
        std::map<int, bool>                                         client_sockets;
        std::map<int, __network *>                                  networks;

        std::map<std::string, __server * >                          servers;       // 127.0.0.1:8080:server_name = {server1, server2 ...}

        std::map<int, __client *>                                   clients;
        std::map<int, std::map<std::string, std::string> >          RequestHeader;
        std::map<int, std::map<std::string, std::string> >          ResponseHeader;
        std::map<std::string, std::string>                          ClientMimeTypes;
        std::map<std::string, std::string>                          ServerMimeTypes;
        std::map<std::string, bool>                                 icons;

    private: __info();
    public: static __info& Instance();


    public:
        std::map<int, _cgi_info>    exec_cgi;
        std::map<int, std::string>  tmp_file;

        void            update_sock(int fd);
        void            add_server_sock(int fd);
        void            add_network(int fd, __network & net);
        void            add_client(int fd, std::string host, std::string port, __server *serv);
        void            rm_client(int fd);
        void            add_RequestHeader(int fd, std::string key, std::string value);
        void            add_ResponseHeader(int fd, std::string key, std::string value);
        void            add_server(std::string host, std::string port, std::string server_name, __server * serv);
        void            set_MimeTypes();
        void            set_all_icons();

        int             max_sock();
        bool            is_server_sock(int fd);
        __network&      network(int fd);
        bool            is_client_sock(int fd);
        __client&       client(int fd);
        std::string     get_RequestHeader(int fd, std::string key);
        std::string     get_ResponseHeader(int fd, std::string key);
        __server *      get_server(std::string host, std::string port, std::string server_name);
        std::string     get_ClientMimeTypes(std::string key);
        std::string     get_ServerMimeTypes(std::string key);
        bool            check_icon(std::string key);

        void            print_header(int fd);
};

__info& Global();

#endif