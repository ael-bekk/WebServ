#ifndef __SERVER_HPP__
#define __SERVER_HPP__

#include "../bits/stdc++.hpp"
#include "../Location/location.hpp"


class __server {
    private:
        std::string                 host;
        std::string                 port;
        std::map<int, std::string>  error_page;
        size_t                      client_max_body_size;
        std::vector <__location>    location;

    public:
        __server(int &line_count, std::ifstream &configfile);
        ~__server();

        std::string                 get_host();
        std::string                 get_port();
        std::map<int, std::string>  get_error_pages();
        size_t                      get_client_max_body_size();
        std::vector<__location>     get_locations();

        int    set_host(std::string host);
        int    set_port(std::string port);
        int    set_error_pages(std::string error, std::string page);
        int    set_client_max_body_size(std::string client_max_body_size);
        int    set_locations(int &line, std::ifstream &configfile, std::stringstream &inp);

        void    ConfigError(int line, std::string detail);
        bool    Insert(std::string key, int &line_count, std::ifstream &configfile, std::stringstream &inp);
};

#endif