#include "response.hpp"
#include "../Info/info.hpp"
#include <sys/types.h>
#include <sys/wait.h>


__response::__response(int sock) :header_log_printed(false), cgi_log_printed(false), cgi_enter(false), sock(sock), location(NULL), in_header(true), in_body(false), content_lent(0), check_err(new __check_err(*this)) {
    this->def_errors["201"] = PAGE_OF("201");
    this->def_errors["204"] = PAGE_OF("204");
    this->def_errors["400"] = PAGE_OF("400");
    this->def_errors["403"] = PAGE_OF("403");
    this->def_errors["404"] = PAGE_OF("404");
    this->def_errors["405"] = PAGE_OF("405");
    this->def_errors["408"] = PAGE_OF("408");
    this->def_errors["411"] = PAGE_OF("411");
    this->def_errors["413"] = PAGE_OF("413");
    this->def_errors["500"] = PAGE_OF("500");
    this->def_errors["501"] = PAGE_OF("501");
    this->def_errors["505"] = PAGE_OF("505");
}

__response::~__response() {
    delete this->location;
}

// sock time path status

void __response::cgi(std::string extension, std::string absolute_path) // trow an error
{
    std::string file;
    std::string stored_exec_file = "./Tmp/";

    mkdir(stored_exec_file.c_str(), S_IRWXU | S_IRWXG);
    NEW_NAME(file);

    stored_exec_file += file + extension;

    int fd = open(stored_exec_file.c_str(), O_CREAT | O_RDWR, 0755);
    if (fd ==- 1)
        EXTMSG("open failed : ");
    
    if (!this->cgi_log_printed)
        cgi_log_printed = true,
        std::cout   << IYellow << this->sock << " : Enter cgi for this path ➔ {" << this->path << "}" << Color_Off << std::endl;
    
    if ((Global().exec_cgi<:this->sock:>.pid = fork()) < 0)
        EXTMSG("fork failed : ");
    if (!Global().exec_cgi<:this->sock:>.pid)
    {
        dup2(fd, 1);
        close(fd);


        char *arr[3] = {strdup("/usr/bin/php-cgi"), strdup(this->path.c_str()), NULL};

        if (execve(arr[0], arr, Global().env) == -1)
            EXTMSG("execve failed : ");
        
    }
    close(fd);
        
    Global().tmp_file[this->sock] = Global().exec_cgi<:this->sock:>.path = stored_exec_file;
}

void __response::cgi_exec(std::string &status) {

    std::string     type;
    time_t          curr_time;

    if (POST() && Global().tmp_file[-this->sock].empty())    return;
    if (POST() && !cgi_enter) path = Global().tmp_file[-this->sock];


    if (this->path.rfind('.') != std::string::npos)
        type = this->path.substr(this->path.rfind('.') + 1);

    if (status == HTTP_200_OK || status == HTTP_201_CREATED || status == HTTP_204_NO_CONTENT) {
        if (!this->location->get_cgi_extension()["." + type].empty()) {
            !cgi_enter && (cgi_enter = true) && (cgi(type, this->location->get_cgi_extension()["." + type]), 1);

            waitpid(Global().exec_cgi<:this->sock:>.pid, &(Global().exec_cgi<:this->sock:>.status), WNOHANG);

            time(&curr_time);

            if (Global().exec_cgi<:this->sock:>.status != -1)
                this->path = Global().exec_cgi<:this->sock:>.path;
            else if (curr_time - Global().exec_cgi<:this->sock:>.tm < 5)
                throw "cgi still hang";
            else
                cgi_enter = false,
                status = HTTP_500_INTERNAL_SERVER_ERROR,
                kill(Global().exec_cgi<:this->sock:>.pid, SIGQUIT);

            if (this->location->get_cgi_extension()["." + type].find("php-cgi") == std::string::npos)
                cgi_enter = false;

            Global().exec_cgi.erase(this->sock);
        }
    }
}

std::string __response::generate_header(std::string status, bool redirected) {
    std::string     _time;
    off_t           lent(0);
    std::string     type;
    std::string     header;
    std::string     int_tostr;
    std::string     delimeter("\r\n");

    this->cgi_exec(status);    

    if (status != HTTP_200_OK && (status != HTTP_201_CREATED || !this->cgi_enter) && status != HTTP_301_MULTIPLE_CHOICE)
        this->path = this->def_errors[status];

    if (this->path.rfind('.') != std::string::npos)
            type = this->path.substr(this->path.rfind('.') + 1);

    CURR_TIME(_time)
    COUNT_CONTENT_LENT(this->path, lent)
    TO_STRING(lent, int_tostr)
    Global().add_ResponseHeader(this->sock, "Content-Length", int_tostr);
    header += "HTTP/1.1 " + status + delimeter;
    header += "Date: " + _time + " GMT" + delimeter;
    if (Global().client(this->sock).get_server())
        header += "Server: " + Global().client(this->sock).get_server()->get_server_name() + delimeter;
    if (!cgi_enter && (int_tostr != "0" || status != HTTP_301_MULTIPLE_CHOICE)) {
        header += "Content-Length: " + int_tostr + delimeter;
        header += "Content-Type: " + Global().get_ClientMimeTypes(type) + delimeter;
    }
    header += "Connection: close" + delimeter;
    if (redirected) header += "Location: " + this->path + delimeter;
    
    if (!cgi_enter) header += delimeter;

    if (!this->header_log_printed)
        header_log_printed = true,
        std::cout   << IBlue << this->sock << " : Header ==> [ \""
                    << status << "\",  \""
                    << this->path << "\",  \""
                    << _time << " GMT" << "\" ]" << Color_Off << std::endl;

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

    try {
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
            if (snd == -1) return SOCK_CLOSE;
        }
    } catch (...) { return SOCK_INIT_STATUS; }

    return RESPONSE_ENDS() ? SOCK_END_RESPONSE : SOCK_INIT_STATUS;
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