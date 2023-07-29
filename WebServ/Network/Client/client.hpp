#ifndef __CLIENT_HPP__
#define __CLIENT_HPP__

#include "../../../bits/API.hpp"

class __client {
    private:
        size_t              infile;
        size_t              outfile;
        __header            header;
        __server            &server;
        __request           request;
        __response          response;

    public:
        __client(__server server);
        ~__client();

        size_t              get_infile();
        size_t              get_outfile();
        __header            get_header();
        __server            get_server();

        void                set_infile(size_t infile);
        void                set_outfile(size_t outfile);
        void                set_header(__header header);
        void                set_server(__server &server);

        void                _insert();
};

#endif