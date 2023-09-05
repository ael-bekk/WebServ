#include "response.hpp"
#include "../Info/info.hpp"

__response::__response(int sock) :sock(sock), location(NULL), in_header(true), in_body(false), content_lent(0), check_err(new __check_err(*this)) {
    this->def_errors["201"] = "./default_error_pages/201.html";
    this->def_errors["204"] = "./default_error_pages/204.html";
    this->def_errors["400"] = "./default_error_pages/400.html";
    this->def_errors["404"] = "./default_error_pages/404.html";
    this->def_errors["405"] = "./default_error_pages/405.html";
    this->def_errors["411"] = "./default_error_pages/411.html";
    this->def_errors["500"] = "./default_error_pages/500.html";
    this->def_errors["501"] = "./default_error_pages/501.html";
    this->def_errors["505"] = "./default_error_pages/505.html";
    // this->def_errors["301"] = "./default_error_pages/204.html";
    // this->def_errors["404"] = "./default_error_pages/204.html";
    // this->def_errors["501"] = "./default_error_pages/204.html";
    // this->def_errors["300"] = "./default_error_pages/204.html";
    // ...........
}

__response::~__response() {
    delete this->location;
}

std::string __response::generate_header(std::string status, bool redirected) {
    std::string     _time;
    int             lent(0);
    std::string     type;
    std::string     header;
    std::string     int_tostr;

    if (status != "200" && status != HTTP_300_MULTIPLE_CHOICE) this->path = this->def_errors[status];

    if (this->path.rfind('.') != std::string::npos)
        type = this->path.substr(this->path.rfind('.') + 1);

    CURR_TIME(_time)
    COUNT_CONTENT_LENT(this->path, lent)
    TO_STRING(lent, int_tostr)
    Global().add_ResponseHeader(this->sock, "Content-Length", int_tostr);
    header += "HTTP/1.1 " + status + std::string("\r\n");
    header += "Date: " + _time + " GMT" + std::string("\r\n");
    header += "Server: " + Global().client(this->sock).get_server().get_server_name() + std::string("\r\n");
    header += "Content-Length: " + int_tostr + std::string("\r\n");
    header += "Content-Type: " + Global().get_ClientMimeTypes(type) + std::string("\r\n");
    header += "Connection: close" + std::string("\r\n");
    if (redirected) header += "Location: " + this->path + std::string("\r\n");
    header += std::string("\r\n");
    return header;
}

std::string __response::Get() {
    return this->generate_header(HTTP_200_OK, NOT_REDIRECTED);
}

std::string __response::Post() {
    return this->generate_header(HTTP_201_CREATED, NOT_REDIRECTED);
}

std::string __response::Delete() {
    return this->generate_header(HTTP_204_NO_CONTENT, NOT_REDIRECTED);
}


std::string __response::error_page() {
    std::string err = GET_RESP_STATUS();
    std::string header;

    std::cout<<"mmmm >>>" << this->path <<std::endl;
    if (err == HTTP_300_MULTIPLE_CHOICE) {
        return this->generate_header(err, REDIRECTED);
    } else {
        this->path.clear();
        
        if ERROR_OVERRIDEN()    this->path = this->errors[err];
        else if DEF_ERROR()     this->path = this->def_errors[err];

        return this->generate_header(err, NOT_REDIRECTED);
    }
    return "";
}

std::string __response::body() {
    char    buffer[BUFFER_SIZE+1];
    int     rd;

    OPEN_INFILE_NOT_OPENED()

    this->infile.read(buffer, BUFFER_SIZE);
    rd = this->infile.gcount();
    content_lent += rd;

    CHECK_READ_ENDS()

    return std::string(buffer, rd);
}

void    __response::set_location(std::string path, std::string req_path, __location *location, std::map<std::string, std::string> error_page) { this->path = path; this->req_path = req_path; this->location = location; this->errors = error_page; }

short    __response::Rspns() {
    std::string block;


    if HEADER_SENDING()
    {
        this->check_err->check_errors();

        if ERROR_OCCURRED()     block = error_page();
        else if POST()          block = this->Post();
        else if GET()           block = this->Get();
        else if DELETE()        block = this->Delete();

        this->in_header = false;
        this->in_body = true;
    }
    else if BODY_SENDING()
        block = body();

    for (int snd = 0; snd != block.length();) {
        block = block.substr(snd);
        snd = send(this->sock, block.c_str(), block.length(), 0);
        if (snd == -1) return (infile.close(), SOCK_CLOSE);
    }

    return RESPONSE_ENDS() ? (infile.close(), SOCK_END_RESPONSE) : SOCK_INIT_STATUS;
}




int                                 __response::get_sock()          { return this->sock; }
bool                                __response::get_in_header()     { return this->in_header; }
bool                                __response::get_in_body()       { return this->in_body; }
int                                 __response::get_content_lent()  { return this->content_lent; }
std::string                         __response::get_req_path()      { return this->req_path; }
std::string                         __response::get_path()          { return this->path; }
std::map<std::string, std::string>  __response::get_def_errors()    { return this->def_errors; }
std::map<std::string, std::string>  __response::get_errors()        { return this->errors; }
__location                          *__response::get_location()     { return this->location; }

void                         __response::set_path(std::string path) { this->path = path; }
