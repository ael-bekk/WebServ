#include "../Declaration/server.hpp"

__server::__server() {}

__server::__server(std::string server_name, std::map<int, std::string> default_err_page)
                : client_max_body_size(3000), server_name(server_name), ip_addr("127.0.0.1"), error_page(default_err_page) {}

__server::__server(__server const & server) {
    *this = server;
}

__server::~__server() {}


std::string __server::get_server_name()                 { return this->server_name; }
std::string __server::get_ip_addr()                     { return this->ip_addr; }
std::vector<unsigned short> __server::get_ports()       { return this->port; }
std::map<int, std::string> __server::get_error_pages()  { return this->error_page; }
size_t __server::get_client_max_body_size()             { return this->client_max_body_size; }
std::vector<__location> __server::get_locations()       { return this->location; }


void __server::set_server_name(std::string server_name)                   { this->server_name = server_name; }
void __server::set_ip_addr(std::string ip_addr)                           { this->ip_addr = ip_addr; }
void __server::set_ports(std::vector<unsigned short> port)                { this->port = port; }
void __server::set_error_pages(std::map<int, std::string>  error_page)    { this->error_page = error_page; }
void __server::set_client_max_body_size(size_t client_max_body_size)      { this->client_max_body_size = client_max_body_size; }
void __server::set_locations(std::vector <__location> location)           { this->location = location; }


void __server::_insert() {
    
}