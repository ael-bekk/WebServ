#include "location.hpp"

__location::__location() : autoindex(false) , root("/"), allow_methods({"GET"}) {}

__location::__location(__location const & location) {
    *this = location;
}

__location::~__location() {}


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


void __location::_insert() {
    
}