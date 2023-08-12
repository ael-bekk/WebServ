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

void    __webserv::InitNetworks()
{    
    int net_size = this->network.size();
    for (int i = 0; i < net_size; i++)
        this->network[i].CreateSocket();
}

void    __webserv::kQue(void)
{

    this->kq.CreateKqueue();
    std::vector<__network> nets = this->network;
    std::cout << "Numbers of networks : " <<  nets.size() << " number of ports inside first networks : " << nets[0].get_Socket().size() << std::endl; 
    for (int i = 0; i < nets.size(); i++)
    {
        std::vector<int> socks = nets[i].get_Socket();
        for (int j = 0; j < socks.size(); j++)
        {
            std::cout << "fd of servers " << socks[j] << std::endl;
            this->kq.add_event(socks[j], EVFILT_READ);
        }
    }
    this->kq.kQueue();

}

void    __webserv::Slct() {

    FD_ZERO(&Select.readable);
    FD_ZERO(&Select.writable);

    for (int i = 0; i < this->network.size(); i++) {
        std::vector<int> sock = this->network[i].get_Socket();
        for (int j = 0; j < sock.size(); j++) {
            FD_SET(sock[j], &Select.readable);
            FD_SET(sock[j], &Select.writable);
        }
    }
    this->Select.multiplexing();
}