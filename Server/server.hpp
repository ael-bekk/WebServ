#ifndef __SERVER_HPP__
#define __SERVER_HPP__

#include "../bits/stdc++.hpp"
#include "../Location/location.hpp"


class __server {
    private:
        std::string                             host;
        std::string                             port;
        std::string                             server_name;
        std::map<std::string, std::string>      error_page;
        unsigned long long                      client_max_body_size;
        std::map <std::string, __location>      location;

    public:
        __server(int &line_count, std::ifstream &configfile);
        ~__server();

        std::string                         get_host();
        std::string                         get_port();
        std::string                         get_server_name();
        std::map<std::string, std::string>  get_error_pages();
        unsigned long long                  get_client_max_body_size();
        std::map <std::string, __location>  get_locations();

        int    set_host(std::string host);
        int    set_port(std::string port);
        int    set_server_name(std::string server_name);
        int    set_error_pages(std::string error, std::string page);
        int    set_client_max_body_size(std::string client_max_body_size);
        int    set_locations(int &line, std::ifstream &configfile, std::stringstream &inp);

        void    ConfigError(int line, std::string detail);
        bool    Insert(std::string key, int &line_count, std::ifstream &configfile, std::stringstream &inp);
};

#endif