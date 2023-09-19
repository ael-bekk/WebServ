#include "request.hpp"
#include "../Info/info.hpp"

__request::__request(int sock) :sock(sock), log_printed(false), header(1), body(0), location(NULL) { this->post = new __post(sock); }

__request::~__request() {
    delete this->location;
    delete this->post;
}

void    __request::InsertFirst(std::stringstream &inp) {
    std::string method, path, http, uri, Query;

    inp >> method >> path >> http;
    if (path.find('?') != std::string::npos)
        Query = path.substr(path.find('?') + 1),
        path = path.substr(0, path.find('?'));
    for (int i = 0, num; i < path.length(); i++)
        if (path[i] == '%' && path.length() - i > 2) {
            STR_HEX_TO_INT(path.substr(i + 1, 2), num)
            uri += char(num);
            i+=2;
        } else
            uri += path[i];
    Global().add_RequestHeader(this->sock, "Method", method);
    Global().add_RequestHeader(this->sock, "Path", uri);
    Global().add_RequestHeader(this->sock, "Query", Query);
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

    while (!buff_rest.empty()) {
        if END_HEADER(this->buff_rest.substr(0, 4))
            return;

        p = buff_rest.find("\r\n");
        if (LINE_DELIMETER(buff_rest.substr(0, 2)) && buff_rest[2] != '\r') {
            buff_rest = buff_rest.substr(2);
        } else if (p && p != std::string::npos) {
            std::string line = buff_rest.substr(0, p);
            buff_rest = buff_rest.substr(p);

            if (GET_REQ_METHOD().empty())
                { std::stringstream S(line); this->InsertFirst(S); }
            else
                this->InsertRest(line);
        } else
            break;
    }
}

void    __request::set_location(std::string p_loc, std::string path, std::string req_path, __location *location) { this->p_loc = p_loc; this->path = path; this->req_path = req_path; this->location = location; }

__location  *__request::get_location() { return location; }

void    __request::MatchServer() {
    std::string host        = Global().client(this->sock).get_host();
    std::string port        = Global().client(this->sock).get_port();
    std::string server_name = GET_REQ_SERVER_NAME();
    
    Global().client(this->sock).set_server(new __server(*Global().get_server(host, port, server_name)));
}

short    __request::HeaderPars() {
    this->InsertData(buff_rest);

    if END_HEADER(this->buff_rest.substr(0, 4))
    {
        buff_rest = buff_rest.substr(4);
        this->header = false;
        this->body = IS_POST(GET_REQ_METHOD());
        this->MatchServer();
    }
    return SOCK_INIT_STATUS;
}


short    __request::BodyPars() {

    unsigned long long max_body_size = Global().client(this->sock).get_server()->get_client_max_body_size();
    if (this->post->open_file_if_not(Global().get_ServerMimeTypes(GET_REQ_CONTENT_TYPE()), p_loc, path, location) != SOCK_INIT_STATUS)
        return SOCK_END_REQUEST;
    if TRANSFER_CHUNKED()
        return  this->post->transfer_encoding_chunked(max_body_size, this->buff_rest);
    if TRANSFER_CONTENT_LENT()
        return  this->post->transfer_content_length(max_body_size, std::atoi(GET_REQ_CONTENT_LENT().c_str()), this->buff_rest);
    return SOCK_END_REQUEST;
}

short    __request::ReadBlock() {
    int r = recv(this->sock, this->buff, BUFFER_SIZE, 0);
 
    if CLIENT_CLOSE(r) {
        this->post->rm_file();
        return SOCK_END_REQUEST_MAX_SIZE;
    }
    this->buff_rest += std::string(this->buff, r);

    return SOCK_INIT_STATUS;
}

short    __request::Rqst() {
    int res = SOCK_INIT_STATUS;
    
    if IS_SOCK_END_REQUEST_MAX_SIZE(ReadBlock()) return SOCK_END_REQUEST_MAX_SIZE;

    this->header && (res = this->HeaderPars());

    this->body && (res = this->BodyPars());

    if (!this->header && !this->log_printed)
        log_printed = true,
        std::cout   << ICyan << this->sock << " : "
                    << Global().get_RequestHeader(this->sock, "Method") << " ➔ "
                    << Global().get_RequestHeader(this->sock, "Path")
                    << Global().get_RequestHeader(this->sock, "Query") << Color_Off << std::endl;

    if (!this->header && !this->body)
        return SOCK_END_REQUEST;

    return res;
}