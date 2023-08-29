#ifndef __RESPONSE_HPP__
#define __RESPONSE_HPP__

#include "../bits/stdc++.hpp"
#include "../Location/location.hpp"
#include "../Check_err/check_err.hpp"

class __location;

class   __response {

    private:
        int                                 sock;
        int                                 infile;
        bool                                in_header;
        bool                                in_body;
        int                                 content_lent;
        std::string                         req_path; // /location/../../...
        std::string                         path;    // /root/location/../../...
        std::map<std::string, std::string>  def_errors;
        std::map<std::string, std::string>  errors;
        __location                          *location;
        __check_err                         check_err;

    public:
        __response(int sock);
        ~__response();
        void    set_location(std::string path, std::string req_path, __location *location, std::map<std::string, std::string> error_page);
        short   Rspns();

        std::string autoindex(); // creat a path and fill it and return it 
        std::string Get();
        std::string Post();
        std::string Delete();
        std::string error_page();
        std::string body();
};

#endif