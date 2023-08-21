#include "network.hpp"

__network::__network(int &line_count, std::ifstream &configfile) : server(line_count, configfile) {}

__network::~__network() {}

__server __network::get_server() { return this->server; }

// getters
int __network::get_Socket() {return this->sock;}
// setters
void    __network::set_Socket(int Socket){ this->sock = Socket; }

void    __network::CreateSocket(void)
{
    int k = 1;
    struct sockaddr_in serv_addr;
    memset(&serv_addr, 0, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = inet_addr(this->get_server().get_host().c_str());
    serv_addr.sin_port = htons(atoi(this->get_server().get_port().c_str()));

    if ((this->sock=socket(PF_INET, SOCK_STREAM, 0)) == -1) {
        std::cerr << "socket() error!\n";
        exit(1);
    }

    if (setsockopt(this->sock, SOL_SOCKET, SO_REUSEADDR, &k, sizeof(int)) < 0) {
        std::cerr << "setsockopt() error!\n";
        exit(1);
    }

    if (bind(this->sock, (struct sockaddr*)&serv_addr, sizeof(serv_addr)) == -1) {
        std::cerr << "bind() error!\n";
        exit(1);
    }

    if (listen(this->sock, 5) == -1) {
        std::cerr << "listen() error!\n";
        exit(1);
    }
    
    this->set_Socket(this->sock);
    Global().update_sock(this->sock);
    Global().add_network(this->sock, *this);

    // lsof -i -P -n | grep LISTEN :: this command to check is all port we listening on you to do infinte loop to check this
    /************************** THIS FOR TESTING IS THE ADDRESS USDED IS THE SAME THAT WE USE *****************************************/
    // char addr[INET6_ADDRSTRLEN];

    // std::cout << rp->ai_flags << std::endl;
    // struct sockaddr_in* saddr = (struct sockaddr_in*)rp->ai_addr;
    // const char* inet_msg = inet_ntop(rp->ai_family, &(saddr->sin_addr), addr, rp->ai_addrlen);
    // if (!inet_msg)
    //     ExitMessage("inet_ntop failed");
    // std::cout << addr << std::endl;

}

int __network::accept_new_client(int serv_sock) {

    int k = 1;
    int clnt_sock;
    sockaddr_in client_addr;
    socklen_t clnt_addr_size = sizeof(client_addr);

    if ((clnt_sock = accept(serv_sock, (sockaddr*)&client_addr, &clnt_addr_size)) == -1)
        EXTMSG("accept() error!");
    
    // if (fcntl(clnt_sock, F_SETFL, fcntl(clnt_sock, F_GETFL, 0) | O_NONBLOCK) == -1)
    //     EXTMSG("fcntl failed");
    if (setsockopt(clnt_sock, SOL_SOCKET, SO_REUSEADDR, &k, sizeof(int)) < 0)
            EXTMSG("setsockopt() error!");

    Global().update_sock(clnt_sock);
    Global().add_client(clnt_sock, NULL);

    return clnt_sock;
}