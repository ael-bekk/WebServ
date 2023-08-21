#include "info.hpp"

__info::__info() : _max(0) {}


__info& __info::Instance()
{
    static __info INSTANCE;
    return INSTANCE;
}

void __info::update_sock(int fd) {
    this->_max = std::max(this->_max, fd);
}

void __info::add_server_sock(int fd) {
    this->server_sockets[fd] = true;
}

void __info::add_network(int fd, __network & net) {
    this->server_sockets[fd] = true;
    this->networks.insert(std::pair<int, __network*>(fd, &net));
}

void __info::add_client(int fd, __server *serv) {
    this->client_sockets[fd] = true;
    this->clients.insert(std::pair<int, __client*>(fd, new __client(fd, serv)));
}

void __info::rm_client(int fd) {
    this->client_sockets[fd] = false;
    delete this->clients[fd];
    this->RequestHeader.erase(fd);
    this->ResponseHeader.erase(fd);
    this->clients.erase(fd);
}

void __info::add_RequestHeader(int fd, std::string key, std::string value) {
    this->RequestHeader[fd][key] = value;
}

void __info::add_ResponseHeader(int fd, std::string key, std::string value) {
    this->ResponseHeader[fd][key] = value;
}



int __info::max_sock() {
    return this->_max;
}

bool __info::is_server_sock(int fd) {
    return this->server_sockets[fd];
}

__network&  __info::network(int fd) {
    return *this->networks[fd];
}


bool __info::is_client_sock(int fd) {
    return this->client_sockets[fd];
}

__client&  __info::client(int fd) {
    return *this->clients[fd];
}

__info& Global() { return __info::Instance(); }

std::string __info::get_RequestHeader(int fd, std::string key) {
    return this->RequestHeader[fd][key];
}

std::string __info::get_ResponseHeader(int fd, std::string key) {
    return this->ResponseHeader[fd][key];
}


void    __info::print_header(int fd) {
    for (auto &it : this->RequestHeader[fd])
        std::cout << it.first << "  ==>  " << it.second << std::endl;
}
