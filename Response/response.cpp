#include "response.hpp"
#include "../Info/info.hpp"

__response::__response(int sock) :sock(sock), infile(-1), location(NULL), in_header(true), in_body(false), content_lent(0) {
    this->def_errors["300"] = "path1";
    this->def_errors["301"] = "path2";
    this->def_errors["404"] = "path3";
    this->def_errors["501"] = "path4";
    this->def_errors["300"] = "path5";
    // ...........
}

__response::~__response() {
    delete this->location;
}


std::string __response::autoindex() {
    std::string path;
    return path;
}

// HTTP/1.1 200 OK
// Date: Mon, 27 Jul 2009 12:28:53 GMT
// Server: Apache/2.2.14 (Win32)
// Content-Length: 88
// Content-Type: text/html

std::string __response::Get() {
    std::string header;
    
    this->path = this->def_errors["200"];

    header += "HTTP/1.1 200 OK";
    header += "";

    return header + SEP_END_RESPONSE;
}

std::string __response::Post() {
    std::string header;

    this->path = this->def_errors["201"];

    header += "HTTP/1.1 201 OK";
    header += "";

    return header + SEP_END_RESPONSE;
}

std::string __response::Delete() {
    std::string header;

    this->path = this->def_errors["204"];

    header += "HTTP/1.1 204 OK";
    header += "";

    return header + SEP_END_RESPONSE;
}


std::string __response::error_page() {
    std::string err = GET_RESP_STATUS();
    std::string header;

    this->path.clear();

    if ERROR_OVERRIDEN()    this->path = this->errors[err];
    else if DEF_ERROR()     this->path = this->def_errors[err];

    // SET_PATH_IF_NOT()

    return header;
}

std::string __response::body() {
    char    buffer[BUFFER_SIZE];
    int     rd;

    OPEN_INFILE_NOT_OPENED()

    rd = read(this->infile, buffer, BUFFER_SIZE);
    
    CHECK_READ_ENDS()

    content_lent += rd;

    return std::string(buffer, rd);
}

void    __response::set_location(std::string path, std::string req_path, __location *location, std::map<std::string, std::string> error_page) { this->path = path; this->req_path = req_path; this->location = location; this->errors = error_page; }

short    __response::Rspns() {
    std::string block;

    std::cout << this->path << " -------- " << this->req_path << std::endl;

    if HEADER_SENDING()
    {
        this->check_err.check_errors();

        if ERROR_OCCURRED()     block = error_page(), this->in_body = true;
        else if POST()          block = this->Post();
        else if GET()           block = this->Get();
        else if DELETE()        block = this->Delete();

        this->in_header = false;
    }
    else if BODY_SENDING()
        block = body();

    int snd = 0;
    do {
        block = block.substr(snd);
        if ((snd = send(this->sock, block.c_str(), block.length(), 0)) == -1)
            return SOCK_CLOSE;
    }   while (snd != block.length());

    return RESPONSE_ENDS() ? SOCK_END_RESPONSE : SOCK_INIT_STATUS;
}