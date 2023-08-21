#ifndef __REQUEST_HPP__
#define __REQUEST_HPP__

#include "../bits/stdc++.hpp"
#include "../Info/info.hpp"


class __request {

    private:
        int         sock;
        int         outfile;
        char        buff[BUFFER_SIZE];
        std::string buff_rest;
        bool        header;
        bool        body;
    public:
        __request(int sock) :sock(sock), header(1), body(0){}

        short    Rqst();

        short   HeaderPars();
        short   ReadBlock();
        void    InsertData(std::string & buff_rest);
        void    InsertFirst(std::stringstream inp);
        void    InsertRest(std::string &line);

        short    BodyPars();

        short    Delete();
        short    Post();
};

#endif