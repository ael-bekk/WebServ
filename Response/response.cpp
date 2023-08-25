#include "response.hpp"
#include "../Info/info.hpp"

__response::__response(int sock) :sock(sock), infile(-1), location(NULL) {}

__response::~__response() {
    delete this->location;
}

void    __response::set_location(std::string path, std::string req_path, __location *location) { this->path = path; this->req_path = req_path; this->location = location; }

short    __response::Rspns() {
    send(this->sock, "HTTP/1.1 200 OK\r\nContent-Length: 88\r\nContent-Type: text/html\r\n\r\n<html><body><h1>Hello, World!</h1></body></html>", strlen("HTTP/1.1 200 OK\r\nContent-Length: 88\r\nContent-Type: text/html\r\n\r\n<html><body><h1>Hello, World!</h1></body></html>") , 0);
    return SOCK_END_RESPONSE;
}