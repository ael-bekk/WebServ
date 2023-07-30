#include "webserv.hpp"

__webserv::__webserv() {}

__webserv::~__webserv() {}

void    ConfigError(int line, std::string detail) {
    cout << "Error : line=" << line << " you print \"" << detail << "\" did you mean \'server {\'" << std::endl;
    exit();
}

void    __webserv::ConfigFile(std::string filename) {
    int line_count = 0;
    std::string line, token, prev_token;
    std::istream configfile(filename);

    if (configfile.fail()) {
        std::cerr << "Error opening file: " << filename << std::endl;
        exit();
    }
    while (std::getline(configfile, line) && ++line_count) {

        stringstream inp(line);

        inp >> token;
        prev_token = token + " ";
        inp >> token;

        if (ENTER_SERVER(prev_token + token) && !(inp >> line))
            network.push_back(__network(line_count, configfile));
        else
            ConfigError(line_count, prev_token + token);
    }
}