#ifndef __POST_HPP__
#define __POST_HPP__

#include "../bits/stdc++.hpp"
#include "../Location/location.hpp"

class __post {

    private:
        std::fstream    outfile;
        int             _pipe[2];
        int             content_length;
        int             count_content_lent;
        bool            cgi;

    public:
        __post();
        short    open_file_if_not(std::string type, std::string p_loc, std::string path, __location  *location);
        short   transfer_encoding_chunked(std::string &buff_rest);
        short   transfer_content_length(int content_lent, std::string &buff_rest);
};

#endif