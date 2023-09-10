#include "network.hpp"
#include "../Info/info.hpp"

__network::__network(int &line_count, std::ifstream &configfile) : server(line_count, configfile) {}

__network::~__network() {}

__server __network::get_server() { return this->server; }
int __network::get_Socket()      { return this->sock; }

void    __network::set_Socket(int Socket){ this->sock = Socket; }

void    __network::CreateSocket(void)
{
    int k = 1;
    struct sockaddr_in serv_addr;

    memset(&serv_addr, 0, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = inet_addr(this->get_server().get_host().c_str());
    serv_addr.sin_port = htons(atoi(this->get_server().get_port().c_str()));

    if ((this->sock=socket(PF_INET, SOCK_STREAM, 0)) == -1)
        EXTMSG("socket() error!")

    if (setsockopt(this->sock, SOL_SOCKET, SO_REUSEADDR, &k, sizeof(int)) < 0)
        EXTMSG("setsockopt() error!")

    if (bind(this->sock, (struct sockaddr*)&serv_addr, sizeof(serv_addr)) == -1)
        EXTMSG("bind() error!")

    if (listen(this->sock, 5) == -1)
        EXTMSG("listen() error!")
    
    this->set_Socket(this->sock);
    Global().update_sock(this->sock);
    Global().add_network(this->sock, *this);

}

int __network::accept_new_client(int serv_sock) {

    int k = 1;
    int clnt_sock;
    sockaddr_in client_addr;
    socklen_t clnt_addr_size = sizeof(client_addr);
    
    // std::cout << "here\n";
    if ((clnt_sock = accept(serv_sock, (sockaddr*)&client_addr, &clnt_addr_size)) == -1)
        EXTMSG("accept() error!")

    if (setsockopt(clnt_sock, SOL_SOCKET, SO_REUSEADDR, &k, sizeof(int)) < 0)
            EXTMSG("setsockopt() error!")

    Global().update_sock(clnt_sock);
    Global().add_client(clnt_sock, this->server.get_host(), this->server.get_port(), NULL);

    return clnt_sock;
}