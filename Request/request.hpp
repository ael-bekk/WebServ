#ifndef __REQUEST_HPP__
#define __REQUEST_HPP__

#include "../bits/stdc++.hpp"
#include "../Location/location.hpp"
#include "../Post/post.hpp"

class __location;
class __post;

class __request {

    private:
        int         sock;
        char        buff[BUFFER_SIZE];
        std::string buff_rest;
        bool        header;
        bool        body;
        bool        log_printed;
        std::string req_path;
        std::string path;
        __location  *location;
        __post      *post;

    public:
        __request(int sock);
        ~__request();

        void    set_location(std::string path, std::string req_path, __location *location);
        __location  *get_location();
        short   Rqst();

        short   HeaderPars();
        short   ReadBlock();
        void    InsertData(std::string & buff_rest);
        void    InsertFirst(std::stringstream &inp);
        int     InsertRest(std::string &line);

        void    MatchServer();
        short   BodyPars();

        short   Delete();
        short   Post();
};

#endif