#ifndef __RESPONSE_HPP__
#define __RESPONSE_HPP__

#include "../bits/stdc++.hpp"

class   __response {

    private:
        int         sock;
        int             infile;
        std::string         location;
    public:
        __response(int sock) :sock(sock), infile(-1) {}

        short    Rspns();

        short    Get();
        short    Post();
        short    Delete();
};

#endif