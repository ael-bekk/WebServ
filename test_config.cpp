#include "WebServ/webserv.hpp"
#include "Info/info.hpp"
using namespace std;

int main(int ac, char **av, char **env) {

    __webserv serv;

    try {
        Global().env = env;
        serv.ConfigFile("config.txt");
        std::vector<__network>  n_tmp = serv.get_networks();
        serv.InitNetworks();
        serv.Slct();
    } catch (std::string &err) {
        std::cout << err << std::endl;
        return 0;
    }
}