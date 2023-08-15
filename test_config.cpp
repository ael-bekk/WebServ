#include "WebServ/webserv.hpp"

using namespace std;

int main() {
    __webserv serv;

    serv.ConfigFile("config.txt");
    // std::vector<__network>  n_tmp = serv.get_networks();
    // for (auto &n : n_tmp) 
    // {
    //     __server s = n.get_server();
    //     cout << s.get_host() << endl;
    //     for (auto m : s.get_ports())
    //         cout << m << "\t";

    //     cout << endl << s.get_client_max_body_size() << endl;
    //     for (auto m : s.get_error_pages())
    //         cout << "{" << m.first << " " << m.second << "}  ";
    //     cout << endl;
    //     for (auto l : s.get_locations()) {
    //         cout << " ----------------------------------------------- " << endl;
    //         cout << l.get_url() << endl;
    //         cout << l.get_root() << endl;
    //         for (auto m : l.get_index())
    //             cout << m << "\t";
    //         cout << endl;
    //         for (auto m : l.get_allow_methods())
    //             cout << m << "\t";
    //         cout << endl << l.get_return().first << " " << l.get_return().second << endl;
    //         cout << l.get_autoindex() << endl;
    //         for (auto m : l.get_cgi_extension())
    //         cout << "{" << m.first << " " << m.second << "}  ";
    //         cout << endl;
    //     }
    // }
    serv.InitNetworks();
    //serv.Slct();
    serv.epl();
}