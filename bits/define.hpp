#ifndef __DEFINE_HPP__
#define __DEFINE_HPP__

#define EXTMSG(str) {                                                            \
                        std::cerr << str << " " << strerror(errno) << std::endl;  \
                        exit(errno);                                               \
                    }

#define ENTER_SERVER(TOKEN) (TOKEN == "server {")

#define MAX_QUEUE 2048

#define IS_HOST(TOKEN)                      (TOKEN == "host")
#define IS_PORT(TOKEN)                      (TOKEN == "port")
#define IS_SERVER_NAME(TOKEN)               (TOKEN == "server_name")
#define IS_ERROR_PAGE(TOKEN)                (TOKEN == "error_page")
#define IS_CLIENT_MAX_BODY_SIZE(TOKEN)      (TOKEN == "client_max_body_size")
#define IS_LOCATION(TOKEN)                  (TOKEN == "location")
#define IS_EXIT(TOKEN)                      (TOKEN == "}")
#define DEFAULT_MAX_BODY_SIZE       3000
#define DEFAULT_PORT                8080
#define LOCALE_HOST                 "127.0.0.1"

#define IS_ROOT(TOKEN)                  (TOKEN == "root")
#define IS_INDEX(TOKEN)                 (TOKEN == "index")
#define IS_ALLOW_METHODS(TOKEN)         (TOKEN == "allow_methods")
#define IS_RETURN(TOKEN)                (TOKEN == "return")
#define IS_AUTOINDEX(TOKEN)             (TOKEN == "autoindex")
#define IS_CGI(TOKEN)                   (TOKEN == "cgi")
#define IS_UPLOAD(TOKEN)                (TOKEN == "upload")
#define IS_EXIT(TOKEN)                  (TOKEN == "}")
#define IS_ENTER(TOKEN)                 (TOKEN == "{")
#define IS_METHOD(TOKEN)                (TOKEN == "GET" || TOKEN == "POST" || TOKEN == "DELETE")
#define IS_ENTER(TOKEN)                 (TOKEN == "{")
#define IS_ENTER(TOKEN)                 (TOKEN == "{")

#define SUCCESS     true
#define FAILURE     false
#define FOUND       true
#define NOT_FOUND   false
#define ON          true
#define OFF         false

#define BUFFER_SIZE 1024

#define CLIENT_CLOSE(X) (X == -1)

#define IS_GET(METHOD)       (METHOD == "GET")
#define IS_POST(METHOD)      (METHOD == "POST")
#define IS_DELETE(METHOD)    (METHOD == "DELETE")

#define CHUNKED_DELIMETER(BUFFER)   (BUFFER == "\r\n")
#define LINE_DELIMETER(BUFFER)    (BUFFER == "\r\n")
#define END_HEADER(BUFFER)      (BUFFER == "\r\n\r\n")


#define END_PARS_RQST       -1
#define PARS_RQST_ENDS(X)   (X == -1)


#define METHOD_POST_TRANSFER_NOT_SUPPORTED        -2
#define SOCK_CLOSE              -1
#define SOCK_INIT_STATUS        0
#define SOCK_END_REQUEST        2
#define SOCK_END_RESPONSE       3

#define IS_METHOD_POST_TRANSFER_NOT_SUPPORTED(STATUS)   (STATUS == -2)
#define IS_SOCK_CLOSED(STATUS)        (STATUS == -1)
#define IS_SOCK_INIT_STATUS(STATUS)   (STATUS == 0)
#define IS_SOCK_END_REQUEST(STATUS)   (STATUS == 2)
#define IS_SOCK_END_RESPONSE(STATUS)  (STATUS == 3)


#define GET_REQ_CONTENT_LENT()           Global().get_RequestHeader(this->sock, "Content-Length")
#define GET_REQ_CONTENT_TYPE()           Global().get_RequestHeader(this->sock, "Content-Type")
#define GET_REQ_METHOD()                 Global().get_RequestHeader(this->sock, "Method")
#define GET_REQ_SERVER_NAME()            Global().get_RequestHeader(this->sock, "host")
#define FILE_NOT_OPEN_YET()              (this->_pipe[0] == -1 && !this->outfile.is_open())
#define TRANSFER_CHUNKED()               (Global().get_RequestHeader(this->sock, "Transfer-Encoding") == "chunked")
#define TRANSFER_CONTENT_LENT()          (!Global().get_RequestHeader(this->sock, "Content-Length").empty())



#define CLEAR_LOCATION_PATH()       {                                                                                                    \
                                        token = "/" + token + "/";                                                                        \
                                        for (int i = 0; i < token.length(); i++)                                                           \
                                            for (path += token[i]; i + 1 < token.length() && token[i] == '/' && token[i + 1] == '/'; i++);  \
                                        for (;path.length() > 1 && path[path.length() - 1] == '/';)                                          \
                                            path.erase(path.length() - 1);                                                                    \
                                    }

#define CLEAR_REQUEST_PATH()        {                                                                                                             \
                                        for (int i = 0; i < tmp_path.length() && tmp_path[i] != '?'; i++)                                          \
                                        for (path += tmp_path[i]; i + 1 < tmp_path.length() && tmp_path[i] == '/' && tmp_path[i + 1] == '/'; i++);  \
                                    }

#define FIND_LOCATION_FROM_PATH()   {                                                                                 \
                                        for(;loc.find(path) == loc.end() && !path.empty();)                            \
                                            path.erase(path.length() - 1);                                              \
                                    }

#define LOCATION_FOUND()            {                                                                         \
                                        actual_path = it->second.get_root() + req_path;                        \
                                        this->request->set_location(actual_path, req_path, new __location(it->second));   \
                                        this->response->set_location(actual_path, req_path, new __location(it->second));   \
                                    }


#define NOT_EMPTY()                      (!line.empty())

#define MIMETYPESFILE               "bits/mime.types.txt"

#define REACH_CONTENT_LENT()    (this->count_content_lent == content_lent)
#define NEED_FOR_NEW_CHUNK()    (!this->count_content_lent && buff_rest.length() >= 7)
#define BODY_ENDS()             (buff_rest.substr(0, 7) == "\r\n0\r\n\r\n")
#define THERE_IS_NEW_CHUNK()    ((pos = buff_rest.find("\r\n", 2)) != std::string::npos)
#define CHUNK_FILLED()          (this->count_content_lent)
#define CORRECT_PATH()          {                                                                      \
                                    filename = path + "/" + location->get_upload() + "/" + filename.substr(0, filename.find('\n', 1)) + "." + type; \
                                    for (int i = 0; i < filename.length(); i++)                           \
                                        (filename[i] == ' ') && (filename[i] = '_');                       \
                                }

#define OPEN_FOR_CGI()          (location->get_upload().empty() && extention.find("." + type) != extention.end())
#define OPEN_FOR_UPLOAD()       (!location->get_upload().empty())


#endif