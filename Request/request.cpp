#include "request.hpp"

void    __request::InsertFirst(std::stringstream inp) {
    std::string method, path, http;

    inp >> method >> path >> http;
    Global().add_RequestHeader(this->sock, "Method", method);
    Global().add_RequestHeader(this->sock, "Path", path);
    Global().add_RequestHeader(this->sock, "Http", http);
}

void    __request::InsertRest(std::string &line) {
    int p = line.find(": ");

    std::string key = line.substr(0, p);
    std::string value = line.substr(p + 2);
    Global().add_RequestHeader(this->sock, key, value);
}

void    __request::InsertData(std::string & buff_rest) {
    int p;
    bool status(true);

    while (!buff_rest.empty() && status) {
        status = false;
        if (END_HEADER(this->buff_rest.substr(0, 4)))
            return;

        if (LINE_DELIMETER(buff_rest.substr(0, 2)) && buff_rest[2] != '\r')
            buff_rest = buff_rest.substr(2),
            status = true;

        p = buff_rest.find("\r\n");
        if (p && p != std::string::npos) {

            std::string line = buff_rest.substr(0, p);
            buff_rest = buff_rest.substr(p);

            if (Global().get_RequestHeader(this->sock, "Method").empty())
                InsertFirst(std::stringstream(line));
            else
                InsertRest(line);

            status = true;
        }
    }
}


short    __request::HeaderPars() {
    int r = recv(sock, this->buff, BUFFER_SIZE, 0);

    if (CLIENT_CLOSE(r))
        return SOCK_CLOSE;

    this->buff_rest += std::string(this->buff, r);

    InsertData(buff_rest);

    if (END_HEADER(this->buff_rest.substr(0, 4))) {
        buff_rest = buff_rest.substr(4);
        this->header = false;
        this->body = IS_POST(Global().get_RequestHeader(this->sock, "Method"));
    }
    return SOCK_INIT_STATUS;
}


short    __request::BodyPars() {
    if (!Global().get_RequestHeader(this->sock, "Content-Length").empty()) {

        return SOCK_INIT_STATUS;
    }
    
    if (!Global().get_RequestHeader(this->sock, "Transfer-Encoding").empty()) {
        if (Global().get_RequestHeader(this->sock, "Transfer-Encoding") == "chunked") {
            
            return SOCK_INIT_STATUS;
        }
    }
    return METHOD_POST_TRANSFER_NOT_SUPPORTED;
}

short    __request::Rqst() {
    int res = SOCK_INIT_STATUS;

    if (this->header)
        res = this->HeaderPars();

    if (this->body)
        res = this->BodyPars();

    if (!this->header)
        Global().print_header(this->sock);
    
    if (!this->header && !this->body)
        return SOCK_END_REQUEST;
    
    return res;
}