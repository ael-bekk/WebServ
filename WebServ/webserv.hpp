#ifndef __WEBSERVE_HPP__
#define __WEBSERVE_HPP__

#include "../bits/stdc++.hpp"
#include "Network/network.hpp"

#define ENTER_SERVER(X) (X == "server {")

class __webserv {
    private:
        std::vector<__network>    network;

    public:
        __webserv();
        ~__webserv();
        void    ConfigError(int line, std::string detail);
        void    ConfigFile(std::string filename);
        
        std::vector<__network>    get_networks();
};

#endif