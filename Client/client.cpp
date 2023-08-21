#include "client.hpp"

__client::__client(int sock, __server *server) : socket(sock), server(server) {
    request = new __request(sock);
    response = new __response(sock);
}

__client::~__client() {
    delete request;
    delete response;
}

size_t  __client::get_socket()  { return this->socket; }

void    __client::set_server(__server *server)  { this->server = server; }


short    __client::Receive() { return this->request->Rqst();}
short    __client::Send()    { return this->response->Rspns();}