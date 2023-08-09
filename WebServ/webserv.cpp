#include "webserv.hpp"

__webserv::__webserv() {}

__webserv::~__webserv() {}

void    __webserv::ConfigError(int line, std::string detail) {
    std::cout << "Error : line=" << line << " you print \"" << detail << "\" did you mean \'server {\'" << std::endl;
    exit(1);
}
std::vector<__network>    __webserv::get_networks() { return this->network; }

void    __webserv::ConfigFile(std::string filename) {
    int line_count = 0;
    std::string line, token, prev_token;
    std::ifstream configfile(filename);

    if (configfile.fail()) {
        std::cerr << "Error opening file: " << filename << std::endl;
        exit(1);
    }
    while (std::getline(configfile, line) && ++line_count) {

        std::stringstream inp(line);

        inp >> token;
        prev_token = token + " ";
        inp >> token;

        if (ENTER_SERVER(prev_token + token) && !(inp >> line))
            network.push_back(__network(line_count, configfile));
        else
            ConfigError(line_count, prev_token + token);
    }
}

void    __webserv::kQueue(void)
{
    
}