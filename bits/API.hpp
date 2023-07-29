#ifndef __API_HPP__
#define __API_HPP__

#include "stdc++.hpp"


#ifdef __WEBSERVE_HPP__
    #include "../WebServ/Network/network.hpp"
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