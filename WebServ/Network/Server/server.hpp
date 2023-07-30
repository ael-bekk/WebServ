#ifndef __SERVER_HPP__
#define __SERVER_HPP__


#include "../../../bits/API.hpp"

class __server {
    private:
        std::string                 host;
        std::vector<unsigned short> port;
        std::map<int, std::string>  error_page;
        size_t                      client_max_body_size;
        std::vector <__location>    location;

    public:
        __server(int &line_count, std::istream &configfile);
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
        int    set_locations(int line, std::istream &configfile);

        void    ConfigError(int line, std::string detail);
        bool    _insert(std::string key, std::string val, std::istream &configfile, std::stringstream &inp);
        void    set_default();
};

#endif