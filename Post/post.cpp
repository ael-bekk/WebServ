#include "post.hpp"

__post::__post() : _pipe{-1, -1}, count_content_lent(0), content_length(0), cgi(false) {}

short    __post::open_file_if_not(std::string type, std::string p_loc, std::string path, __location  *location) {
    if FILE_NOT_OPEN_YET() {

        NEW_NAME(this->filename)

        std::map<std::string, std::string> extention = location->get_cgi_extension();

        CORRECT_PATH()

        if OPEN_FOR_UPLOAD()
        {
            this->outfile.open(std::string(this->filename), std::ios::out);
            if (!this->outfile.is_open()) {
                return SOCK_END_REQUEST;
            }
        }
        if OPEN_FOR_CGI()
        {
            if (pipe(this->_pipe))
                return SOCK_END_REQUEST;
            this->cgi = true;
        } /*else error*/
    }
    return SOCK_INIT_STATUS;
}

short   __post::transfer_encoding_chunked(unsigned long long max_body_size, std::string &buff_rest) {
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
                STR_HEX_TO_INT(buff_rest.substr(0, pos), this->count_content_lent)
                this->content_length += this->count_content_lent;
                std::cout << max_body_size << std::endl;
                if (this->content_length > max_body_size) {
                    this->outfile.close();
                    remove(this->filename.c_str());
                    return  SOCK_END_REQUEST_MAX_SIZE;
                }
                buff_rest = buff_rest.substr(pos + 2);
            }
        }

        if CHUNK_FILLED()
        {
            read_chunk = !!buff_rest.length();
            pos = std::min(this->count_content_lent, static_cast<unsigned long long>(buff_rest.length()));
            outfile << buff_rest.substr(0, pos);
            this->count_content_lent -= pos;
            buff_rest = buff_rest.substr(pos);
        }
    }

    return SOCK_INIT_STATUS;
}

short   __post::transfer_content_length(unsigned long long max_body_size, int content_lent, std::string &buff_rest) {

    int pos;
std::cout << content_lent << " " << max_body_size << std::endl;
    if (content_lent > max_body_size) {
        this->outfile.close();
        remove(this->filename.c_str());
        return  SOCK_END_REQUEST_MAX_SIZE;
    }

    pos = std::min(content_lent - this->count_content_lent, static_cast<unsigned long long>(buff_rest.length()));
    this->count_content_lent += pos;

    outfile << buff_rest.substr(0, pos);
    buff_rest = buff_rest.substr(pos);

    if REACH_CONTENT_LENT() {
        this->outfile.close();
        this->content_length = this->count_content_lent;
        return SOCK_END_REQUEST;
    }

    return SOCK_INIT_STATUS;
}