#ifndef __SERVER_HPP__
#define __SERVER_HPP__

#include "../../../bits/stdc++.hpp"
#include "Location/location.hpp"
#define IS_HOST(X)                      (X == "host")
#define IS_PORT(X)                      (X == "port")
#define IS_ERROR_PAGE(X)                (X == "error_page")
#define IS_CLIENT_MAX_BODY_SIZE(X)      (X == "client_max_body_size")
#define IS_LOCATION(X)                  (X == "location")
#define IS_EXIT(X)                      (X == "}")
#define DEFAULT_MAX_BODY_SIZE       3000
#define DEFAULT_PORT                8080
#define LOCALE_HOST                 "127.0.0.1"

class __server {
    private:
        std::string                 host;
        std::vector<unsigned short> port;
        std::map<int, std::string>  error_page;
        size_t                      client_max_body_size;
        std::vector <__location>    location;

    public:
        __server(int &line_count, std::ifstream &configfile);
        ~__server();

        std::string                 get_host();
        std::vector<unsigned short> get_ports();
        std::map<int, std::string>  get_error_pages();
        size_t                      get_client_max_body_size();
        std::vector<__location>     get_locations();

        int    set_host(std::string host);
        int    set_ports(std::string port);
        int    set_error_pages(std::string error, std::string page);
        int    set_client_max_body_size(std::string client_max_body_size);
        int    set_locations(int &line, std::ifstream &configfile, std::stringstream &inp);

        void    ConfigError(int line, std::string detail);
        bool    _insert(std::string key, int &line_count, std::ifstream &configfile, std::stringstream &inp);
};

#endif