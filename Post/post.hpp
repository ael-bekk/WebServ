#ifndef __POST_HPP__
#define __POST_HPP__

#include "../bits/stdc++.hpp"
#include "../Location/location.hpp"

class __post {

    private:
        std::string     filename;
        std::fstream    outfile;
        unsigned long long             content_length;
        unsigned long long             count_content_lent;
        bool            cgi;

    public:
        __post();

        void    rm_file();
        short   open_file_if_not(std::string type, std::string p_loc, std::string path, __location  *location);
        short   transfer_encoding_chunked(unsigned long long max_body_size, std::string &buff_rest);
        short   transfer_content_length(unsigned long long max_body_size, int content_lent, std::string &buff_rest);
};

#endif