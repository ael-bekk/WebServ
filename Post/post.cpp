#include "post.hpp"

__post::__post() : _pipe{-1, -1}, cgi(false) {}

void    __post::open_file_if_not(std::string path, __location  *location) {
    if FILE_NOT_OPEN_YET() {
        std::time_t result = std::time(nullptr);
        std::string filename = std::asctime(std::localtime(&result));
        std::map<std::string, std::string> extention = location->get_cgi_extension();
        int dot_pos = path.find_last_of('.');
        
        for (int i = 0; i < filename.length(); i++)
            (filename[i] == ' ') && (filename[i] = '_');
        
        if (dot_pos != std::string::npos && extention.find(path.substr(dot_pos)) != extention.end()) {
            if (pipe(this->_pipe))
                EXTMSG("pipe() error!")
            this->cgi = true;
        } else {
            this->outfile.open(filename, std::ios::out);
            if (!this->outfile.is_open())
                EXTMSG("open() error!")
        }
    }
}

short   __post::transfer_encoding_chunked(std::string path, __location  *location) {
    this->open_file_if_not(path, location);
    
    return SOCK_INIT_STATUS;
}

short   __post::transfer_content_length(std::string path, __location  *location) {
    this->open_file_if_not(path, location);

    return SOCK_INIT_STATUS;
}