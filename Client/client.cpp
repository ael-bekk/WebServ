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
size_t  __client::get_infile()  { return this->infile; }
size_t  __client::get_outfile() { return this->outfile; }

void    __client::set_infile(size_t infile)     { this->infile = infile; }
void    __client::set_outfile(size_t outfile)   { this->outfile = outfile; }
void    __client::set_server(__server *server)  { this->server = server; }


bool    __client::Send()    { /*return this->response->Rspns();*/return 1; }
bool    __client::Receive() { return this->request->Rqst(); }