#ifndef __RESPONSE_HPP__
#define __RESPONSE_HPP__

#include "../bits/stdc++.hpp"
#include "../Location/location.hpp"
#include "../Check_err/check_err.hpp"

class __location;
class __check_err;

class   __response {

    private:
        bool                                cgi_enter;
        int                                 sock;
        std::ifstream                       infile;
        bool                                in_header;
        bool                                in_body;
        bool                                header_log_printed;
        bool                                cgi_log_printed;
        int                                 content_lent;
        std::string                         req_path;
        std::string                         path;
        std::map<std::string, std::string>  def_errors;
        std::map<std::string, std::string>  errors;
        __location                          *location;
        __check_err                         *check_err;

    public:
        __response(int sock);
        ~__response();
        void    set_location(std::string path, std::string req_path, __location *location, std::map<std::string, std::string> error_page);
        short   Rspns();

        int                                 get_sock();
        bool                                get_in_header();
        bool                                get_in_body();
        int                                 get_content_lent();
        std::string                         get_req_path();
        std::string                         get_path();
        std::map<std::string, std::string>  get_def_errors();
        std::map<std::string, std::string>  get_errors();
        __location                          *get_location();

        void        cgi(std::string extension, std::string absolute_path);
        void        cgi_exec(std::string &status);
        
        void                                set_path(std::string path);
        std::string generate_header(std::string status, bool redirected);
        std::string Get();
        std::string Post();
        std::string Delete();
        std::string error_page();
        std::string body();
};

#endif