#include "WebServ/webserv.hpp"
#include "Info/info.hpp"
using namespace std;

int main(int ac, char **av, char **env) {

    __webserv serv;
    try {
        Global().env = env;
        serv.ConfigFile("config.txt");
        std::vector<__network>  n_tmp = serv.get_networks();
        // for (auto &n : n_tmp) 
        // {
        //     __server s = n.get_server();
        //     cout << s.get_host() << endl;
        //     cout << s.get_port() << "\t";

        //     cout << endl << s.get_client_max_body_size() << endl;
        //     for (auto m : s.get_error_pages())
        //         cout << "{" << m.first << " " << m.second << "}  ";
        //     cout << endl;
        //     for (auto l : s.get_locations()) {
        //         cout << " ----------------------------------------------- " << endl;
        //         cout << l.first << endl;
        //         cout << l.second.get_root() << endl;
        //         for (auto m : l.second.get_index())
        //             cout << m << "\t";
        //         cout << endl;
        //         for (auto m : l.second.get_allow_methods())
        //             cout << m << "\t";
        //         cout << endl << l.second.get_return().first << " " << l.second.get_return().second << endl;
        //         cout << l.second.get_autoindex() << endl;
        //         for (auto m : l.second.get_cgi_extension())
        //         cout << "{" << m.first << " " << m.second << "}  ";
        //         cout << endl;
        //     }
        // }
        serv.InitNetworks();
        serv.Slct();
        // serv.epl();
    } catch (std::string &err) { std::cout << err << std::endl; return 0; }
}