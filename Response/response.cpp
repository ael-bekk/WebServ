#include "response.hpp"

short    __response::Rspns() {
    send(this->sock, "HTTP/1.1 200 OK\r\nContent-Length: 88\r\nContent-Type: text/html\r\n\r\n<html><body><h1>Hello, World!</h1></body></html>", strlen("HTTP/1.1 200 OK\r\nContent-Length: 88\r\nContent-Type: text/html\r\n\r\n<html><body><h1>Hello, World!</h1></body></html>") , 0);
    return SOCK_END_RESPONSE;
}