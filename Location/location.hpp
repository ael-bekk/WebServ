#ifndef __LOCATION_HPP__
#define __LOCATION_HPP__

#include "../bits/stdc++.hpp"


class __location {
    private:
        std::string                                         path;
        std::string                                         root;
        std::vector<std::string>                            index;
        std::map<std::string, bool>                         allow_methods;
        std::pair<int, std::string>                         _return;
        bool                                                autoindex;
        std::string                                         upload;
        std::map<std::string, std::string>                  cgi_extension;

    public:
        __location(int &line_count, std::ifstream &configfile);
        ~__location();

        std::string                         get_root();
        std::vector<std::string>            get_index();
        std::map<std::string, bool>         get_allow_methods();
        std::pair<int, std::string>         get_return();
        bool                                get_autoindex();
        std::map<std::string, std::string>  get_cgi_extension();
        std::string                         get_upload();

        bool    set_root(std::stringstream &inp);
        bool    set_index(std::stringstream &inp);
        bool    set_allow_methods(std::stringstream &inp);
        bool    set_return(std::stringstream &inp);
        bool    set_autoindex(std::stringstream &inp);
        bool    set_cgi_extension(std::stringstream &inp);
        bool    set_upload(std::stringstream &inp);

        void    ConfigError(int line, std::string detail);
        bool    Insert(std::string key, std::stringstream &inp); // set all location infos
};

#endif