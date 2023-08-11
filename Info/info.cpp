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

void __info::add_client_sock(int fd) {
    this->client_sockets[fd] = true;
}

void __info::add_client(int fd, __client & clt) {
    this->client_sockets[fd] = true;
    this->clients.insert(std::pair<int, __client*>(fd, &clt));
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