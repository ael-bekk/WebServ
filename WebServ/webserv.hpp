#ifndef __WEBSERVE_HPP__
#define __WEBSERVE_HPP__

#include "../bits/API.hpp"

class __webserv {
    private:
        std::vector<__network>    network;

    public:
        __webserv();
        ~__webserv();
        void    ConfigError(int line, std::string detail);
        void    ConfigFile(std::string filename);
};

#endif