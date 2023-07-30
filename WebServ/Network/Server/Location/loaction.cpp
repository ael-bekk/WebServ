#include "location.hpp"

__location::__location(int &line_count, std::istream &configfile) {
    std::string line, key, val;

    set_default();
    while (std::getline(configfile, line) && ++line_count) {
        std::stringstream inp(line);

        inp >> key;
        if (IS_EXIT(key)) break;
        if (!(inp >> val) || !_insert(key, val, configfile) || inp >> val)
            ConfigError(line_count, key);
    }
}

__location::~__location() {}


void    __location::set_default() {
    autoindex = ON;
    this->root = this->url;
    if (!allow_methods.size()) allow_methods.push_back("GET");
}

void __location::_insert() {
}

void    ConfigError(int line, std::string detail) {
    cout << "Error : line=" << line << " in the location block ==> \"" << detail << "\"" << std::endl;
    exit();
}

std::string __location::get_root()                                                  { return this->root; }
std::vector<std::string> __location::get_index()                                    { return this->index; }
std::vector<std::string> __location::get_allow_methods()                            { return this->allow_methods; }
std::pair<int, std::string> __location::get_return()                                { return this->_return; }
bool __location::get_autoindex()                                                    { return this->autoindex; }
std::vector<std::pair<std::string, std::string>> __location::get_cgi_extension()    { return this->cgi_extension; }


void __location::set_root(std::string root)                                                         { this->root = root; }
void __location::set_index(std::vector<std::string> index)                                          { this->index = index; }
void __location::set_allow_methods(std::vector<std::string> allow_methods)                          { this->allow_methods = allow_methods; }
void __location::set_return(std::pair<int, std::string> _return)                                    { this->_return = _return; }
void __location::set_autoindex(bool autoindex)                                                      { this->autoindex = autoindex; }
void __location::set_cgi_extension(std::vector<std::pair<std::string, std::string>> cgi_extension)  { this->cgi_extension = cgi_extension; }