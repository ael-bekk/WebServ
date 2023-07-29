#ifndef __SERVER_HPP__
#define __SERVER_HPP__


#include "../../../bits/API.hpp"

class __server {
    private:
        std::string                 server_name;
        std::string                 ip_addr;
        std::vector<unsigned short> port;
        std::map<int, std::string>  error_page;
        size_t                      client_max_body_size;
        std::vector <__location>    location;
    public:
        __server();
        __server(std::string server_name, std::map<int, std::string> default_err_page);
        __server(__server const & server);
        ~__server();

        std::string                 get_server_name();
        std::string                 get_ip_addr();
        std::vector<unsigned short> get_ports();
        std::map<int, std::string>  get_error_pages();
        size_t                      get_client_max_body_size();
        std::vector<__location>     get_locations();

        void    set_server_name(std::string server_name);
        void    set_ip_addr(std::string ip_addr);
        void    set_ports(std::vector<unsigned short> port);
        void    set_error_pages(std::map<int, std::string>  error_page);
        void    set_client_max_body_size(size_t client_max_body_size);
        void    set_locations(std::vector <__location> location);
        
        void    _insert(); // set all server infos
};

#endif