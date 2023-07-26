#ifndef __SERVER_CPP__
#define __SERVER_CPP__

#include "../../bits/stdc++.h"
#include "location.hpp"

class __server {
    private:
        std::string                 server_name;
        std::string                 host;
        std::vector<unsigned short> listen;
        std::map<int, std::string>  error_page;
        size_t                      client_max_body_size;
        std::vector <__location>    location;
    public:
        __server();
        ~__server();
        __server(__server const & server);
        __server &operator=(__server const & server);

};

#endif