#ifndef __LOCATION_HPP__
#define __LOCATION_HPP__

#include "../../bits/stdc++.h"

class __location {
    private:
        std::string                         root;
        std::vector<std::string>            index;        
        std::vector<std::string>            allow_methods;
        std::pair<int, std::string>         _return;
        bool                                autoindex;
        std::vector<std::pair<std::string, std::string>> cgi_extension;
    public:
        __location();
        ~__location();
        __location(__location const & location);
        __location & operator= (__location const & location);

        std::string                         get_root();
        std::vector<std::string>            get_index();
        std::vector<std::string>            get_allow_methods();
        std::pair<int, std::string>         get_return();
        bool                                get_autoindex();
        std::vector<std::pair<std::string, std::string>> get_cgi_extension();

        void    set_root(std::string root);
        void    set_index(std::vector<std::string> index);
        void    set_allow_methods(std::vector<std::string> allow_methods);
        void    set_return(std::pair<int, std::string> _return);
        void    set_autoindex(bool autoindex);
        void    set_cgi_extension(std::vector<std::pair<std::string, std::string>> cgi_extension);

        void    _insert(); // set all location infos
};

#endif