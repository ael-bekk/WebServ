#ifndef __POST_HPP__
#define __POST_HPP__

#include "../bits/stdc++.hpp"
#include "../Location/location.hpp"

class __post {

    private:
        std::fstream    outfile;
        int             _pipe[2];
        int             content_lent;
        bool            cgi;

    public:
        __post();
        void    open_file_if_not(std::string path, __location  *location);
        short   transfer_encoding_chunked(std::string path, __location  *location);
        short   transfer_content_length(std::string path, __location  *location);
};

#endif