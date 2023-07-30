#ifndef __API_HPP__
#define __API_HPP__

#include "stdc++.hpp"

#define SUCCESS     true
#define FOUND       true
#define FAILURE     false
#define NOT_FOUND   false
#define ON          true
#define OFF         false


/*                    ►   files tree   ◄            

├► bits     ⤵
|           ├⟚ API.hpp
|           ├⟚ stdc++.hpp
|
|
├► WebServ  ⤵
|           ├⟚ webserv.hpp
|           ├⟚ webserv.cpp
|           ├► Network   ⤵
|                        ├⟚ network.hpp
|                        ├⟚ network.cpp
|                        ├► Client   ⤵
|                        |           ├⟚ client.hpp
|                        |           ├⟚ client.cpp
|                        |           ├► Request  ⤵
|                        |           |           ├⟚ request.hpp
|                        |           |           ├⟚ request.cpp
|                        |           |
|                        |           |
|                        |           ├► Response ⤵
|                        |                       ├⟚ response.hpp
|                        |                       ├⟚ response.cpp
|                        |                       ├► Get     ⤵
|                        |                       |          ├⟚ get.hpp
|                        |                       |          ├⟚ get.cpp
|                        |                       |
|                        |                       |
|                        |                       ├► Post    ⤵
|                        |                       |          ├⟚ post.hpp
|                        |                       |          ├⟚ post.cpp
|                        |                       |
|                        |                       |
|                        |                       ├► Delete ⤵
|                        |                                  ├⟚ delete.hpp
|                        |                                  ├⟚ delete.cpp
|                        |
|                        |
|                        ├► Server  ⤵
|                                    ├⟚ server.hpp
|                                    ├⟚ server.cpp 
|                                    ├► Location ⤵
|                                                ├⟚ location.hpp
|                                                ├⟚ location.cpp

*/

/*                          hpp headers                     */

#ifdef __WEBSERVE_HPP__
    #include "../WebServ/Network/network.hpp"
    
    #define ENTER_SERVER(X) (X == "server {")
#endif

#ifdef __NETWORK_HPP__
    #include <netdb.h>      // header file for network-related functions and structures (e.g., getaddrinfo)
    #include <netinet/in.h> // header file for internet protocol-related functions and structures (e.g., sockaddr_in)
    #include <sys/socket.h> // header file for socket programming functions and structures (e.g., socket, bind, listen, accept)
    #include <arpa/inet.h>  // header file for internet protocol-related functions (e.g., inet_addr, inet_ntoa)
    
    #include "../WebServ/Network/Server/server.hpp"
    #include "../WebServ/Network/Client/client.hpp"
#endif

#ifdef __LOCATION_HPP__
#endif

#ifdef __SERVER_HPP__
    #include "../WebServ/Network/Server/Location/location.hpp"

    #define IS_HOST(X)                  (X == "host")
    #define IS_PORT(X)                  (X == "port")
    #define IS_ERROR_PAGE(X)            (X == "error_page")
    #define IS_CLIENT_MAX_BODY_SIZE(X)  (X == "client_max_body_size")
    #define IS_LOCATION(X)              (X == "location")
    #define IS_EXIT(X)                  (X == "}")
    #define DEFAULT_MAX_BODY_SZ     3000
    #define DEFAULT_PORT            8080
    #define LOCALE_HOST             "127.0.0.1"

#endif

#ifdef __HEADER_HPP__
#endif

#ifdef __CLIENT_HPP__
    #include "../WebServ/Network/Server/server.hpp"
    #include "../WebServ/Network/Client/Header/header.hpp"
    #include "../WebServ/Network/Client/Request/request.hpp"
    #include "../WebServ/Network/Client/Response/response.hpp"
#endif

#ifdef __REQUEST_HPP__
#endif

#ifdef __RESPONSE_HPP__
#endif

#endif