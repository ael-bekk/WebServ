#ifndef __LOCATION_HPP__
#define __LOCATION_HPP__

#include "../../../../bits/stdc++.hpp"
#define IS_PATH(X)                   (X == "path")
#define IS_ROOT(X)                  (X == "root")
#define IS_INDEX(X)                 (X == "index")
#define IS_ALLOW_METHODS(X)         (X == "allow_methods")
#define IS_RETURN(X)                (X == "return")
#define IS_AUTOINDEX(X)             (X == "autoindex")
#define IS_CGI(X)                   (X == "cgi")
#define IS_EXIT(X)                  (X == "}")
#define IS_ENTER(X)                 (X == "{")
#define IS_METHOD(X)                (X == "GET" || X == "POST" || X == "DELETE")
#define IS_ENTER(X)                 (X == "{")
#define IS_ENTER(X)                 (X == "{")

class __location {
    private:
        std::string                                         path;
        std::string                                         root;
        std::vector<std::string>                            index;
        std::vector<std::string>                            allow_methods;
        std::pair<int, std::string>                         _return;
        bool                                                autoindex;
        std::map<std::string, std::string>                  cgi_extension;

    public:
        __location(int &line_count, std::ifstream &configfile, std::stringstream &inp);
        ~__location();

        std::string                         get_url();
        std::string                         get_root();
        std::vector<std::string>            get_index();
        std::vector<std::string>            get_allow_methods();
        std::pair<int, std::string>         get_return();
        bool                                get_autoindex();
        std::map<std::string, std::string>  get_cgi_extension();

        bool    set_url(std::stringstream &inp);
        bool    set_root(std::stringstream &inp);
        bool    set_index(std::stringstream &inp);
        bool    set_allow_methods(std::stringstream &inp);
        bool    set_return(std::stringstream &inp);
        bool    set_autoindex(std::stringstream &inp);
        bool    set_cgi_extension(std::stringstream &inp);

        void    ConfigError(int line, std::string detail);
        bool    _insert(std::string key, std::stringstream &inp); // set all location infos
};

#endif