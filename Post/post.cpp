#include "post.hpp"

__post::__post(int sock) : sock(sock), count_content_lent(0), content_length(0), cgi(false) {}

short    __post::open_file_if_not(std::string tp, std::string path, __location  *location) {
    std::map<std::string, std::string> extention = location->get_cgi_extension();

    std::string type = tp;
    if FILE_NOT_OPEN_YET() {

        NEW_NAME(this->filename)


        CORRECT_PATH()

        if (path.rfind('.') != std::string::npos) {
            type = path.substr(path.rfind('.') + 1);
            if OPEN_FOR_CGI() this->filename += '.' + type;
        }

        if (OPEN_FOR_UPLOAD() || OPEN_FOR_CGI())
            this->outfile.open(this->filename.c_str(), std::ios::out);
        else
            return SOCK_END_REQUEST;

        if (!this->outfile.is_open())
            return SOCK_END_REQUEST;

        
        if OPEN_FOR_CGI()
            Global().tmp_file[-this->sock] = this->filename;
    }
    return SOCK_INIT_STATUS;
}

void __post::rm_file() {
    remove(this->filename.c_str());
}

short   __post::transfer_encoding_chunked(unsigned long long max_body_size, std::string &buff_rest) {
    int pos;
    bool read_chunk(true);

    while (read_chunk) {
        read_chunk = false;

        if NEED_FOR_NEW_CHUNK()
        {
            if BODY_ENDS()
                return (this->outfile.close(), SOCK_END_REQUEST);
    
            if THERE_IS_NEW_CHUNK()
            {
                STR_HEX_TO_INT(buff_rest.substr(0, pos), this->count_content_lent)
                this->content_length += this->count_content_lent;

                if (this->content_length > max_body_size)
                    return  (this->rm_file(), SOCK_END_REQUEST_MAX_SIZE);
        
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
    
    if (content_lent > max_body_size) {
        this->rm_file();
        return  (this->outfile.close(), SOCK_END_REQUEST_MAX_SIZE);
    }

    pos = std::min(content_lent - this->count_content_lent, static_cast<unsigned long long>(buff_rest.length()));
    this->count_content_lent += pos;

    outfile << buff_rest.substr(0, pos);
    buff_rest = buff_rest.substr(pos);

    if REACH_CONTENT_LENT() {
        this->content_length = this->count_content_lent;
        return (this->outfile.close(), SOCK_END_REQUEST);
    }

    return SOCK_INIT_STATUS;
}