#ifndef __DEFINE_HPP__
#define __DEFINE_HPP__

#define EXTMSG(str) {\
    std::cout << str << " " << strerror(errno) << std::endl; \
    exit(errno); \
}

#define ENTER_SERVER(TOKEN) (TOKEN == "server {")

#define MAX_QUEUE 2048

#define IS_HOST(TOKEN)                      (TOKEN == "host")
#define IS_PORT(TOKEN)                      (TOKEN == "port")
#define IS_ERROR_PAGE(TOKEN)                (TOKEN == "error_page")
#define IS_CLIENT_MAX_BODY_SIZE(TOKEN)      (TOKEN == "client_max_body_size")
#define IS_LOCATION(TOKEN)                  (TOKEN == "location")
#define IS_EXIT(TOKEN)                      (TOKEN == "}")
#define DEFAULT_MAX_BODY_SIZE       3000
#define DEFAULT_PORT                8080
#define LOCALE_HOST                 "127.0.0.1"

#define IS_PATH(TOKEN)                  (TOKEN == "path")
#define IS_ROOT(TOKEN)                  (TOKEN == "root")
#define IS_INDEX(TOKEN)                 (TOKEN == "index")
#define IS_ALLOW_METHODS(TOKEN)         (TOKEN == "allow_methods")
#define IS_RETURN(TOKEN)                (TOKEN == "return")
#define IS_AUTOINDEX(TOKEN)             (TOKEN == "autoindex")
#define IS_CGI(TOKEN)                   (TOKEN == "cgi")
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

#define LINE_DELIMETER(BUFFER)   (BUFFER == "\r\n")
#define END_HEADER(BUFFER)       (BUFFER == "\r\n\r\n")


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


#endif