#ifndef __RESPONSE_HPP__
#define __RESPONSE_HPP__

#include "../bits/stdc++.hpp"
#include "../Location/location.hpp"

class __location;

class   __response {

    private:
        int         sock;
        int         infile;

        std::string req_path; // /location/../../...
        std::string path;    // /root/location/../../...

        __location  *location;

    public:
        __response(int sock);
        ~__response();
        void    set_location(std::string path, std::string req_path, __location *location);
        short   Rspns();

        short   Get();
        short   Post();
        short   Delete();
};

#endif