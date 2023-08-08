#include "location.hpp"

__location::__location(int &line_count, std::ifstream &configfile, std::stringstream &inp) {
    std::string line, key;

    if (!Insert("path", inp))
        ConfigError(line_count, key);
    while (std::getline(configfile, line) && ++line_count) {
        std::stringstream inp(line);

        inp >> key;
        if (IS_EXIT(key)) break;
        if (!Insert(key, inp))
            ConfigError(line_count, key);
    }
}

__location::~__location() {}

bool __location::Insert(std::string key, std::stringstream &inp) {
    int ret = FAILURE;

    if (IS_PATH(key))
        ret = set_url(inp);
    else if (IS_ROOT(key))
        ret = set_root(inp);
    else if (IS_INDEX(key))
        ret = set_index(inp);
    else if (IS_ALLOW_METHODS(key))
        ret = set_allow_methods(inp);
    else if (IS_RETURN(key))
        ret = set_return(inp);
    else if (IS_AUTOINDEX(key))
        ret = set_autoindex(inp);
    else if (IS_CGI(key))
        ret = set_cgi_extension(inp);
    return ret;
}

void    __location::ConfigError(int line, std::string detail) {
    std::cout << "Error : line=" << line << " in the location block ==> \"" << detail << "\"" << std::endl;
    exit(1);
}

std::string __location::get_url()                                       { return this->path; }
std::string __location::get_root()                                      { return this->root; }
std::vector<std::string> __location::get_index()                        { return this->index; }
std::vector<std::string> __location::get_allow_methods()                { return this->allow_methods; }
std::pair<int, std::string> __location::get_return()                    { return this->_return; }
bool __location::get_autoindex()                                        { return this->autoindex; }
std::map<std::string, std::string> __location::get_cgi_extension()      { return this->cgi_extension; }

bool    __location::set_url(std::stringstream &inp) {
    std::string end;
    if (!(inp >> this->path) || !(inp >> end) || !IS_ENTER(end) || inp >> end)
        return FAILURE;
    return SUCCESS;
}

bool    __location::set_root(std::stringstream &inp) {
    std::string end;
    if (!(inp >> this->root) || inp >> end)
        return FAILURE;
    return SUCCESS;
}

bool    __location::set_index(std::stringstream &inp) {
    std::string index;
    while (inp >> index)
        this->index.push_back(index);
    return SUCCESS;
}

bool    __location::set_allow_methods(std::stringstream &inp) {
    std::string allow_method;
    while (inp >> allow_method)
       if (IS_METHOD(allow_method))
            this->allow_methods.push_back(allow_method);
        else
            return FAILURE;
    return SUCCESS;
}

bool    __location::set_return(std::stringstream &inp) {
    int err, end;
    std::string r;
    if (!(inp >> err) || !(inp >> r) || inp >> end)
        return FAILURE;
    this->_return.first = err;
    this->_return.second = r;
    return SUCCESS;
}

bool    __location::set_autoindex(std::stringstream &inp) {
    std::string status, end;
    if (!(inp >> status) || inp >> end || !(status == "ON" || status == "OFF"))
        return FAILURE;
    this->autoindex = (status == "ON");
    return SUCCESS;
}

bool    __location::set_cgi_extension(std::stringstream &inp) {
    std::string path, extention, end;
    if (!(inp >> extention) || !(inp >> path) || inp >> end)
        return FAILURE;
    this->cgi_extension[extention] = path;
    return SUCCESS;
}