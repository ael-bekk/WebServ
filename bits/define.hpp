#ifndef __DEFINE_HPP__
#define __DEFINE_HPP__

#define EXTMSG(str) {\
    std::cout << str << " " << strerror(errno) << std::endl; \
    exit(errno); \
}

#define ENTER_SERVER(X) (X == "server {")

#define MAX_QUEUE 2048

#define IS_HOST(X)                      (X == "host")
#define IS_PORT(X)                      (X == "port")
#define IS_ERROR_PAGE(X)                (X == "error_page")
#define IS_CLIENT_MAX_BODY_SIZE(X)      (X == "client_max_body_size")
#define IS_LOCATION(X)                  (X == "location")
#define IS_EXIT(X)                      (X == "}")
#define DEFAULT_MAX_BODY_SIZE       3000
#define DEFAULT_PORT                8080
#define LOCALE_HOST                 "127.0.0.1"

#define IS_PATH(X)                   (X == "path")
#define IS_ROOT(X)                  (X == "root")
#define IS_INDEX(X)                 (X == "index")
#define IS_ALLOW_METHODS(X)         (X == "allow_methods")
#define IS_RETURN(X)                (X == "return")
#define IS_AUTOINDEX(X)             (X == "autoindex")
#define IS_CGI(X)                   (X == "cgi")
#define IS_EXIT(X)                  (X == "}")
#define IS_ENTER(X)                 (X == "{")
#define IS_METHOD(X)                (X == "GET" || X == "POST" || X == "DELETE")
#define IS_ENTER(X)                 (X == "{")
#define IS_ENTER(X)                 (X == "{")

#define SUCCESS     true
#define FAILURE     false
#define FOUND       true
#define NOT_FOUND   false
#define ON          true
#define OFF         false


#define BUFFER_SIZE 1024

#define CLIENT_CLOSE(X) (X == -1)

#define IS_GET(X)       (X == "GET")
#define IS_POST(X)      (X == "POST")
#define IS_DELETE(X)    (X == "DELETE")

#define LINE_DELIMETER(X)   (X == "\r\n")
#define END_HEADER(X)       (X == "\r\n\r\n")

#define FAIL(X) (!X)

#endif