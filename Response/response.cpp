#include "response.hpp"
#include "../Info/info.hpp"
#include <sys/types.h>
#include <sys/wait.h>

std::string __response::cgi(std::string extension, std::string absolute_path)
{
    std::string ext;
    std::string file;
    std::string stored_exec_file = "/goinfre/";
    int status;

    NEW_NAME(file);
    file += extension;

    stored_exec_file += file;


    int fd = open(file.c_str(), O_CREAT | O_RDWR, 0755);
    if (fd ==- 1)
        EXTMSG("open failed : ");
    
    int id = fork();
    if (id < 0)
        EXTMSG("fork failed : ");
    if (id == 0)
    {
        dup2(fd, 1);
        char *arr[3];
        
        arr[0] = strdup(absolute_path.c_str());
        arr[1] = strdup(this->path.c_str());
        arr[2] = NULL;

        if (execve(arr[0], arr, NULL) == -1)
            EXTMSG("execve failed : ");
        
    }
    //waitpid(-1, &status, WNOHANG); // we will work with this
    wait(&status);
    
    return (stored_exec_file);
}

__response::__response(int sock) :sock(sock), location(NULL), in_header(true), in_body(false), content_lent(0), check_err(new __check_err(*this)) {
    this->def_errors["201"] = PAGE_OF("201");
    this->def_errors["204"] = PAGE_OF("204");
    this->def_errors["400"] = PAGE_OF("400");
    this->def_errors["403"] = PAGE_OF("403");
    this->def_errors["404"] = PAGE_OF("404");
    this->def_errors["405"] = PAGE_OF("405");
    this->def_errors["411"] = PAGE_OF("411");
    this->def_errors["413"] = PAGE_OF("413");
    this->def_errors["500"] = PAGE_OF("500");
    this->def_errors["501"] = PAGE_OF("501");
    this->def_errors["505"] = PAGE_OF("505");
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
    std::string     delimeter("\r\n");

    if (status != HTTP_200_OK && status != HTTP_301_MULTIPLE_CHOICE) this->path = this->def_errors[status];

    if (this->path.rfind('.') != std::string::npos)
        type = this->path.substr(this->path.rfind('.') + 1);

    CURR_TIME(_time)
    COUNT_CONTENT_LENT(this->path, lent)
    TO_STRING(lent, int_tostr)
    Global().add_ResponseHeader(this->sock, "Content-Length", int_tostr);
    header += "HTTP/1.1 " + status + delimeter;
    header += "Date: " + _time + " GMT" + delimeter;
    header += "Server: " + Global().client(this->sock).get_server().get_server_name() + delimeter;
    if (int_tostr != "0" || status != HTTP_301_MULTIPLE_CHOICE) {
        header += "Content-Length: " + int_tostr + delimeter;
        header += "Content-Type: " + Global().get_ClientMimeTypes(type) + delimeter;
    }
    header += "Connection: close" + delimeter;
    if (redirected) header += "Location: " + this->path + delimeter;
    header += delimeter;
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

    if (err == HTTP_301_MULTIPLE_CHOICE) {
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

void    __response::set_location(std::string path, std::string req_path, __location *location, std::map<std::string, std::string> error_page) {
    this->path = path;
    this->req_path = req_path;
    this->location = location;
    this->errors = error_page;
}

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