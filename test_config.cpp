#include "WebServ/webserv.hpp"
#include "Info/info.hpp"
using namespace std;

int main(int ac, char **av, char **env) {

    __webserv serv;
    if (ac != 2) {
        std::cout << UGreen << "usage : " << Color_Off << BIRed << "\n\t./serv /path/to/config.conf" << Color_Off << std::endl;
        return 0;
    }
    try {
        Global().env = env;
        serv.ConfigFile(av[1]);
        std::vector<__network>  n_tmp = serv.get_networks();
        serv.InitNetworks();
        serv.Slct();
    } catch (std::string &err) {
        std::cout << err << std::endl;
        return 0;
    }
}