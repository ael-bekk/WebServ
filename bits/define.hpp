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
#define IS_OTHER_METHOD(TOKEN)          (TOKEN == "HEAD" || TOKEN == "PUT" || TOKEN == "CONNECT" || TOKEN == "OPTIONS" || TOKEN == "TRACE" || TOKEN == "PATCH")
#define IS_ENTER(TOKEN)                 (TOKEN == "{")
#define IS_ENTER(TOKEN)                 (TOKEN == "{")

#define SUCCESS         true
#define FAILURE         false
#define FOUND           true
#define NOT_FOUND       false
#define ON              true
#define OFF             false
#define REDIRECTED      true
#define NOT_REDIRECTED  false

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


#define SOCK_CLOSE                  -1
#define SOCK_INIT_STATUS            0
#define SOCK_END_REQUEST            2
#define SOCK_END_RESPONSE           3
#define SOCK_END_REQUEST_MAX_SIZE   4

#define IS_SOCK_CLOSED(STATUS)                          (STATUS == -1)
#define IS_SOCK_INIT_STATUS(STATUS)                     (STATUS == 0)
#define IS_SOCK_END_REQUEST(STATUS)                     (STATUS == 2)
#define IS_SOCK_END_RESPONSE(STATUS)                    (STATUS == 3)
#define IS_SOCK_END_REQUEST_MAX_SIZE(STATUS)            (STATUS == 4)


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
                                        this->request->set_location(path, actual_path, req_path, new __location(it->second));   \
                                        this->response->set_location(actual_path, req_path, new __location(it->second), this->server->get_error_pages());   \
                                    }

#define TO_STRING(NUM, STR)                 {                                \
                                                std::stringstream ss;         \
                                                ss << NUM;                     \
                                                STR = ss.str();                 \
                                            }

#define TO_INT(STR, NUM)                    {                                \
                                                std::stringstream ss(STR);    \
                                                ss >> NUM;                     \
                                            }

#define STR_HEX_TO_INT(STR, NUM)            {                                \
                                                std::istringstream inp(STR);  \
                                                inp >> std::hex >> NUM;        \
                                            }

#define NOT_EMPTY()                      (!line.empty())

#define MIMETYPESFILE               "bits/mime.types.txt"

#define REACH_CONTENT_LENT()    (this->count_content_lent == content_lent)
#define NEED_FOR_NEW_CHUNK()    (!this->count_content_lent && buff_rest.length() >= 7)
#define BODY_ENDS()             (buff_rest.substr(0, 7) == "\r\n0\r\n\r\n")
#define THERE_IS_NEW_CHUNK()    ((pos = buff_rest.find("\r\n", 2)) != std::string::npos)
#define CHUNK_FILLED()          (this->count_content_lent)

#define NEW_NAME(FILENAME)      {                                                                                                    \
                                    std::time_t result = std::time(NULL);                                                             \
                                    FILENAME = std::string(std::asctime(std::localtime(&result))).substr(0, FILENAME.find('\n', 1));   \
                                    FILENAME = FILENAME.substr(0, FILENAME.find('\n', 1));                                              \
                                    for (int i = 0; i < FILENAME.length(); i++)                                                          \
                                        (FILENAME[i] == ' ') && (FILENAME[i] = '_');                                                      \
                                }
#define CURR_TIME(TIME)         {                                                                                                       \
                                    std::time_t result = std::time(NULL);                                                             \
                                    TIME = std::string(std::asctime(std::localtime(&result))).substr(0, TIME.find('\n', 1));   \
                                    TIME = TIME.substr(0, TIME.find('\n', 1));                                                  \
                                }
#define CORRECT_PATH()          filename = location->get_root() + p_loc + "/" + location->get_upload() + "/" + filename + "." + type;

#define OPEN_FOR_CGI()          (location->get_upload().empty() && extention.find("." + type) != extention.end())
#define OPEN_FOR_UPLOAD()       (!location->get_upload().empty())

#define ERROR_OCCURRED()        (!Global().get_ResponseHeader(this->sock, "status").empty())
#define POST()                  (Global().get_RequestHeader(this->sock, "Method") == "POST")
#define GET()                   (Global().get_RequestHeader(this->sock, "Method") == "GET")
#define DELETE()                (Global().get_RequestHeader(this->sock, "Method") == "DELETE")
#define HEADER_SENDING()        (this->in_header)
#define BODY_SENDING()          (this->in_body)
#define RESPONSE_ENDS()        (!this->in_body)
#define ERROR_OVERRIDEN()       (!this->errors[err].empty())
#define DEF_ERROR()             (!this->def_errors[err].empty())

#define OPEN_INFILE_NOT_OPENED()    {                                                       \
                                        if (!this->infile.is_open())                              \
                                            this->infile.open(this->path.c_str());\
                                    }

#define GET_RESP_STATUS()                 Global().get_ResponseHeader(this->sock, "status")
#define GET_RESP_CONTENT_LENT()           Global().get_ResponseHeader(this->sock, "Content-Length")
#define GET_RESP_CONTENT_TYPE()           Global().get_ResponseHeader(this->sock, "Content-Type")
#define GET_RESP_METHOD()                 Global().get_ResponseHeader(this->sock, "Method")
#define GET_RESP_SERVER_NAME()            Global().get_ResponseHeader(this->sock, "host")

#define CHECK_READ_ENDS()   {                                                                           \
                                int content;                                                             \
                                TO_INT(GET_RESP_CONTENT_LENT(), content)                                  \
                                if (rd == -1 || content == this->content_lent)                             \
                                    this->in_body = false;                                                  \
                                rd = (rd == -1) ? 0 : rd;                                                    \
                            }

#define SEP_RESPONSE                "/r/n"
#define SEP_END_RESPONSE            "/r/n/r/n"

#define COUNT_CONTENT_LENT(PATH, LENT)      {                                      \
                                                FILE *f = fopen(PATH.c_str(), "r"); \
                                                if (f != NULL) {                     \
                                                    fseek(f, 0, SEEK_END);            \
                                                    LENT = ftell(f);                   \
                                                    fclose(f);                          \
                                                }                                        \
                                            }

#define AUTO_INDEXING()                 (path[path.length() - 1] == '/')

#define FILE_OPENED(FILE_NAME, STATUS)          {               \
                                                    FILE *f = fopen(FILE_NAME.c_str(), "r"); \
                                                    STATUS = (f != NULL);\
                                                    STATUS && fclose(f);\
                                                }

////////////////////////// http status ==============?
#define HTTP_200_OK                             "200"
#define HTTP_201_CREATED                        "201"
#define HTTP_204_NO_CONTENT                     "204"

#define HTTP_301_MULTIPLE_CHOICE                "301"

#define HTTP_404_NOT_FOUND                      "404"
#define HTTP_405_METHOD_NOT_ALLOWED             "405"
#define HTTP_411_LENGTH_REQUIRE                 "411"
#define HTTP_400_BAD_REQUEST                    "400"
#define HTTP_501_NOT_IMPLEMENTED                "501"
#define HTTP_505_HTTP_VERSION_NOT_SUPPORTED     "505"
#define HTTP_403_FORBIDDEN                      "403"

#define HTTP_413_PAYLOAD_TOO_LARGE              "413"

#define HTTP_408_REQUEST_TIMEOUT                "408"
#define HTTP_410_GONE                           "410"
#define HTTP_500_INTERNAL_SERVER_ERROR          "500"
#define HTTP_507_INSUFFICIENT_STORAGE           "507"
#define HTTP_508_LOOP_DETECTED                  "508"

////////////// AUTOINDEX
#define HTML_UP_BODY(PATH) "<!DOCTYPE html>\n<html lang='en'>\n<head>\n <meta charset='UTF-8'>\n <meta name='viewport' content='width=device-width, initial-scale=1.0'>\n <title>Auto Index Page</title>\n <style>\
                            body {\n   font-family: Arial, sans-serif;\n   background-color: #4d4343;\n   margin: 0;\n   padding: 0;\n  }\n\n  header {\n   background-color: #333;\n   color: #b17a7a;\n   padding: 10px 0;\n   text-align: center;\n   box-shadow: 0 0 30px 6px #0a0a0abe;\n   margin-bottom: 50px;\n  }\n\n  h1 {\n   margin: 0;\n  }\n\n  h2 {\n   text-align: center;\n  }\n  .container {\n   max-width: 800px;\n   margin: 20px auto;\n   background-color: #c0c0c0;\n   padding: 20px;\n   box-shadow: 0 0 30px 6px #0a0a0abe;\n   border-radius: 5px;\n  }\n\n  ul {\n   list-style: none;\n   padding: 0;\n  }\n\n  li {\n   margin: 10px 0;\n \n display: flex; \n justify-content: space-between; \n }\n\n  a {\n   text-decoration: none;\n   color: #103b69;\n  }\n\n  a:hover {\n   text-decoration: none;\n   color: #a200ff;\n  }\n\n  a:active {\n   text-decoration: none;\n   color: #44006b;\n  }\n  \n  .file-icon {\n   width: 30px;\n   vertical-align: middle;\n  }\n  .go-back-link-container {\n   display: flex;\n   justify-content: center;\n   align-items: center;\n   margin-top: 20px;\n  }\n  .go-back-link {\n   display: inline-block;\n   margin-top: 20px;\n   padding: 5px 10px;\n   background-color: #103b69;\n   color: #fff;\n   border-radius: 5px;\n   text-decoration: none;\n   transition: background-color 0.3s;\n  }\n\n  .go-back-link:hover {\n   background-color: #015dc0;\n   color: #7c7c7c;\n  }\n  .go-back-link:active {\n   background-color: #58a6fa;\n   color: #363636;\n  }\n .delete-button {\n background-color: #ff0000;\n color: #fff;\n border: none;\n padding: 5px 10px;\n border-radius: 5px;\n cursor: pointer;\n transition: background-color 0.3s;\n }\n .delete-button:hover {\n background-color: #cc0000;\n }\n .delete-button:active {\n background-color: #990000;\n .delete-button-container {\n text-align: right;\n } .file-info {\n flex-grow: 1;\n } } </style>\
                            </head>\n<body>\n <header>\n  <h1>Auto Index Page</h1>\n </header>\n <div class='container'>\n  <h2>"+PATH+"</h2>\n  <ul>"

#define HTML_DOWN_BODY "</ul><div class='go-back-link-container'><a href='../' class='go-back-link'>Go Back</a></div><script>\
        function deleteFile(filePath) {\
            fetch(`${encodeURIComponent(filePath)}`, {\
                method: 'DELETE',\
            })\
            .then(response => {\
                if (response.ok) {\
                    console.log('File deleted successfully');\
                    window.location.reload();\
                } else {\
                    console.error('Error deleting file');\
                }\
            })\
            .catch(error => {\
                console.error('Error:', error);\
            });\
        }\
    </script></body></html>"

#define HTML_DOCUMENT(SRC, HREF, NAME) ("<li><div class='file-info'><img src='"+SRC+"' class='file-icon'> <a href='"+HREF+"'>"+NAME+"</a></div> <div class='delete-button-container'><button  class='delete-button' onclick=deleteFile(\""+HREF+"\")>Delete</button></div></li>")

#define ICONS_HOST  std::string("https://raw.githubusercontent.com/ael-bekk/WebServ/main/icons/")
#define OLD_DIR     std::string("..")
#define CUR_DIR     std::string(".")

#define PAGE_OF(ERR) ("./default_error_pages/"+std::string(ERR)+".html")

#endif