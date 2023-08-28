#include "post.hpp"

__post::__post() : _pipe{-1, -1}, count_content_lent(0), content_length(0), cgi(false) {}

void    __post::open_file_if_not(std::string type, std::string path, __location  *location) {
    if FILE_NOT_OPEN_YET() {
        std::time_t result = std::time(NULL);
        std::string filename = std::asctime(std::localtime(&result));
        std::map<std::string, std::string> extention = location->get_cgi_extension();

        CORRECT_PATH()
        
        if OPEN_FOR_UPLOAD()
        {
            this->outfile.open(std::string(filename), std::ios::out);
            if (!this->outfile.is_open())
                EXTMSG("open() error!")
        }
        if OPEN_FOR_CGI()
        {
            if (pipe(this->_pipe))
                EXTMSG("pipe() error!")
            this->cgi = true;
        } /*else error*/
    }
}

short   __post::transfer_encoding_chunked(std::string &buff_rest) {
    int pos;
    bool read_chunk(true);

    while (read_chunk) {
        read_chunk = false;

        if NEED_FOR_NEW_CHUNK()
        {
            if BODY_ENDS()
            {
                this->outfile.close();
                return SOCK_END_REQUEST;
            }
            if THERE_IS_NEW_CHUNK()
            {
                std::istringstream inp(buff_rest.substr(0, pos));
                inp >> std::hex >> this->count_content_lent;
                this->content_length += this->count_content_lent;
                buff_rest = buff_rest.substr(pos + 2);
            }
        }

        if CHUNK_FILLED()
        {
            read_chunk = !!buff_rest.length();
            pos = std::min(this->count_content_lent, int(buff_rest.length()));
            outfile << buff_rest.substr(0, pos);
            this->count_content_lent -= pos;
            buff_rest = buff_rest.substr(pos);
        }
    }

    return SOCK_INIT_STATUS;
}

short   __post::transfer_content_length(int content_lent, std::string &buff_rest) {

    int pos;
    
    pos = std::min(content_lent - this->count_content_lent, int(buff_rest.length()));

    outfile << buff_rest.substr(0, pos);
    this->count_content_lent += pos;
    buff_rest = buff_rest.substr(pos);
    if REACH_CONTENT_LENT()
    {
        this->outfile.close();
        this->content_length == this->count_content_lent;
        return SOCK_END_REQUEST;
    }
    return SOCK_INIT_STATUS;
}