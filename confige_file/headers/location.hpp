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
        std::pair<std::string, std::string> cgi_extension;
    public:
        __location();
        ~__location();
        __location(__location const & location);
        __location & operator= (__location const & location);

        
};

#endif