#ifndef __CHECK_ERR_HPP__
#define __CHECK_ERR_HPP__

#include "../bits/stdc++.hpp"
#include "../Response/response.hpp"
#include "../Info/info.hpp"

class __response;

class __check_err {
    private:
        __response *response;        
        int         sock;
    public:
        __check_err(__response &obj);
        void check_post();
        void check_get();
        void check_delete();
        std::string autoindex(std::string path);
        bool header_err();
        void check_errors();
};

#endif