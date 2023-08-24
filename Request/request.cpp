#include "request.hpp"
#include "../Info/info.hpp"

__request::__request(int sock) :sock(sock), header(1), body(0), location(NULL) {}

__request::~__request() {
    delete this->location;
}

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
                this->InsertFirst(std::stringstream(line));
            else
                this->InsertRest(line);

            status = true;
        }
    }
}

void    __request::set_location(std::string path, __location *location) { this->path_req = path; this->location = location; }

void    __request::MatchServer() {
    std::string host        = Global().client(this->sock).get_host();
    std::string port        = Global().client(this->sock).get_port();
    std::string server_name = Global().get_RequestHeader(this->sock, "host");
    // std::cout << Global().is_client_sock(this->sock) << " " << this->sock << std::endl;
    Global().client(this->sock).set_server(new __server(*Global().get_server(host, port, server_name)));
    // std::cout << Global().get_server(host, port, server_name)->get_host() << std::endl;
}

short    __request::HeaderPars() {
    this->InsertData(buff_rest);

    if (END_HEADER(this->buff_rest.substr(0, 4))) {
        buff_rest = buff_rest.substr(4);
        this->header = false;
        this->body = IS_POST(Global().get_RequestHeader(this->sock, "Method"));
        this->MatchServer();
    }
    return SOCK_INIT_STATUS;
}


short    __request::BodyPars() {
    if (!Global().get_RequestHeader(this->sock, "Content-Length").empty()) {

        return SOCK_INIT_STATUS;
    } else if (Global().get_RequestHeader(this->sock, "Transfer-Encoding") == "chunked") {

        return SOCK_INIT_STATUS;
    }

    return METHOD_POST_TRANSFER_NOT_SUPPORTED;
}

short    __request::ReadBlock() {
    int r = recv(this->sock, this->buff, BUFFER_SIZE, 0);
    if (CLIENT_CLOSE(r))
        return SOCK_CLOSE;
    this->buff_rest += std::string(this->buff, r);
    return SOCK_INIT_STATUS;
}

short    __request::Rqst() {
    int res = SOCK_INIT_STATUS;
    
    if (IS_SOCK_CLOSED(ReadBlock())) return SOCK_CLOSE;

    this->header && (res = this->HeaderPars());

    this->body && (res = this->BodyPars());

    if (!this->header)
        Global().print_header(this->sock);
    
    if (!this->header && !this->body)
        return SOCK_END_REQUEST;

    return res;
}