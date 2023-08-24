#ifndef __REQUEST_HPP__
#define __REQUEST_HPP__

#include "../bits/stdc++.hpp"
#include "../Location/location.hpp"

class __location;

class __request {

    private:
        int         sock;
        int         outfile;
        char        buff[BUFFER_SIZE];
        std::string buff_rest;
        bool        header;
        bool        body;
        std::string path_req;
        __location  *location;
    public:
        __request(int sock);
        ~__request();
        void    set_location(std::string path, __location *location);
        short   Rqst();

        short   HeaderPars();
        short   ReadBlock();
        void    InsertData(std::string & buff_rest);
        void    InsertFirst(std::stringstream inp);
        void    InsertRest(std::string &line);

        void    MatchServer();
        short   BodyPars();

        short   Delete();
        short   Post();
};

#endif