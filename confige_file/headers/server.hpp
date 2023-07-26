#ifndef __SERVER_CPP__
#define __SERVER_CPP__

#include "../../bits/stdc++.h"
#include "location.hpp"

class __server {
    private:
        std::string                 server_name;
        std::string                 host;
        std::vector<unsigned short> port;
        std::map<int, std::string>  error_page;
        size_t                      client_max_body_size;
        std::vector <__location>    location;
    public:
        __server();
        ~__server();
        __server(__server const & server);
        __server &operator=(__server const & server);

        std::string                 get_server_name();
        std::string                 get_host();
        std::vector<unsigned short> get_ports();
        std::map<int, std::string>  get_error_pages();
        size_t                      get_client_max_body_size();
        std::vector<__location>     get_locations();

        void    set_server_name();
        void    set_host();
        void    set_ports();
        void    set_error_pages();
        void    set_client_max_body_size();
        void    set_locations();
        
        void    _set(); // set all server infos
};

#endif