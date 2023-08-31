#include "response.hpp"
#include "../Info/info.hpp"

__response::__response(int sock) :sock(sock), infile(-1), location(NULL), in_header(true), in_body(false), content_lent(0) {
    this->def_errors["201"] = "./default_error_pages/201.html";
    this->def_errors["204"] = "./default_error_pages/204.html";
    this->def_errors["500"] = "path1";
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
    std::string path_autoindex;
    DIR* dir = opendir(this->path.c_str());
    struct dirent* list;
    int fd;

    NEW_NAME(path_autoindex);
    std::string tmp = "/goinfre/";
    tmp += path_autoindex;
    tmp += ".html";

    std::cout << "this is the file : " << tmp << std::endl;
    fd = open(tmp.c_str(),  O_CREAT | O_TRUNC  | O_RDWR, 0755);
    if (fd == -1)
        EXTMSG("open failed inside autoindex");
    if (dir == NULL)
        EXTMSG("opendir failed");

    std::string html_file;
    html_file = "<!DOCTYPE html>"\
            "<html lang=\"en\">"\
            "<head>" \
            "<meta charset=\"UTF-8\">"\
            "<meta name=\"viewport\" content=\"width=device-width, initial-scale=1.0\">"\
            "<title>Document</title>"\
            "</head>"\
            "<style>" \
            "a:link {"\
            "color: green;"\
            "background-color: transparent;"\
            "text-decoration: none;"\
            "}"\
            "a:visited { color: pink; background-color: transparent; text-decoration: none; }"\
            "a:hover { color: red;background-color: transparent;text-decoration: underline; }"\
            "a:active { color: yellow; background-color: transparent; text-decoration: underline; } "\
            "</style>"\
            "<body>";

    std::string html_copy = html_file;
    if (write(fd, html_copy.c_str(), html_copy.size()) <= 0)
        EXTMSG("write failed ");
    
    while ((list = readdir(dir)) != NULL)
    {
        
        html_copy += "\n <p><a href=";
        html_copy += list->d_name;
        html_copy += ">";
        html_copy += list->d_name;
        html_copy += "</a></p>";
        if (write(fd, html_copy.c_str(), html_copy.size()) <= 0)
            EXTMSG("write failed ");
        html_copy = "";
    }
    html_copy += "</body></html>";
    if (write(fd, html_copy.c_str(), html_copy.size()) <= 0)
        EXTMSG("write failed ");
    closedir(dir);
    close (fd);
    return tmp;

}

void __response::standard_header(std::string &header, std::string status, std::string first_line) {
    std::string     _time;
    int             lent(0);
    std::string     type;
    if (status != "200") this->path = this->def_errors[status];
    if (this->path.rfind('.') != std::string::npos)
        type = this->path.substr(this->path.rfind('.') + 1);
    header += first_line + std::string("\r\n");
    CURR_TIME(_time)
    header += "Date: " + _time + " GMT" + std::string("\r\n");
    header += "Server: " + Global().client(this->sock).get_server().get_server_name() + std::string("\r\n");
    COUNT_CONTENT_LENT(this->path, lent)
    Global().add_ResponseHeader(this->sock, "Content-Length", std::to_string(lent));
    header += "Content-Length: " + std::to_string(lent) + std::string("\r\n");
    header += "Content-Type: " + Global().get_ClientMimeTypes(type) + std::string("\r\n");
    header += "Connection: close" + std::string("\r\n");
    header += std::string("\r\n");
}

std::string __response::Get() {
    std::string     header;

    if AUTO_INDEXING()
        this->path = this->autoindex();
    this->standard_header(header, "200", "HTTP/1.1 200 OK");

    return header;
}

std::string __response::Post() {
    std::string     header;

    this->standard_header(header, "201", "HTTP/1.1 201 Created");
    std::cout<<"hhhh >>>" << header<<std::endl;
    return header;
}

std::string __response::Delete() {
    std::string header;

    this->standard_header(header, "204", "HTTP/1.1 204 No Content");

    return header;
}


std::string __response::error_page() {
    std::string err = GET_RESP_STATUS();
    std::string header;

    this->path.clear();

    if ERROR_OVERRIDEN()    this->path = this->errors[err];
    else if DEF_ERROR()     this->path = this->def_errors[err];

    this->standard_header(header, err, ("HTTP/1.1 " + err));

    return header;
}

std::string __response::body() {
    char    buffer[BUFFER_SIZE+1];
    int     rd;

    OPEN_INFILE_NOT_OPENED()
    // std::cout << this->infile  << "\n";

    rd = read(this->infile, buffer, BUFFER_SIZE);
    // std::cout << "1" << "\n";
    
    // std::cout << "2" << "\n";

    // std::cout << "path :::: " << this->sock << " " << rd << " " << content_lent << " " << std::stoi(Global().get_ResponseHeader(this->sock, "Content-Length")) << "\n";
    content_lent += rd;

    CHECK_READ_ENDS()
    // std::cout << this->in_body;
    // std::cout << std::string(buffer, rd) << "\n";

    return std::string(buffer, rd);
}

void    __response::set_location(std::string path, std::string req_path, __location *location, std::map<std::string, std::string> error_page) { this->path = path; this->req_path = req_path; this->location = location; this->errors = error_page; }

short    __response::Rspns() {
    std::string block;


    if HEADER_SENDING()
    {
        // std::cout << this->path << " ----resp---- " << this->req_path << std::endl;
        // this->check_err.check_errors();

        if ERROR_OCCURRED()     block = error_page(), this->in_body = true;
        else if POST()          block = this->Post();
        else if GET()           block = this->Get();
        else if DELETE()        block = this->Delete();

        this->in_header = false;
        this->in_body = true;
    }
    else if BODY_SENDING()
        block = body();
    // std::cout << " " << block.length() << " " << "\n";

    int snd = 0;
    while (snd != block.length()) {
        block = block.substr(snd);
        snd = send(this->sock, block.c_str(), block.length(), 0);
        // std::cout << " " << snd << " ***" << "\n";
        if (snd == -1)
            return (close(infile), SOCK_CLOSE);
    }
    
    return RESPONSE_ENDS() ? (close(infile), SOCK_END_RESPONSE) : SOCK_INIT_STATUS;
}