#ifndef __RESPONSE_HPP__
#define __RESPONSE_HPP__

#include "../bits/stdc++.hpp"

class   __response {

    private:
        int         sock;
    public:
        __response(int sock) :sock(sock) {}

        bool    Rspns();

        bool    Get();
        bool    Post();
        bool    Delete();
};

#endif