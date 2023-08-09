#include "network.hpp"

__network::__network(int &line_count, std::ifstream &configfile) : server(line_count, configfile) {}

__network::~__network() {}

__server __network::get_server() { return this->server; }

// getters
std::vector<int> __network::get_Socket() {return this->sock;}
// setters
void    __network::set_Socket(int Socket){ this->sock.push_back(Socket); }

void    __network::CreateSocket(void)
{
  
    memset(&this->hints, 0, sizeof(this->hints));
    this->hints.ai_family = AF_INET;
    this->hints.ai_socktype = SOCK_STREAM;
    
   
    int BIND_STATUS = 0;
    int fd_sock;
    
    // this loop assign each port to the same address 
    for (int i = 0; i < this->server.get_ports().size(); i++)
    {
        int getaddrinfo_status = getaddrinfo(this->server.get_host().c_str(), (this->server.get_ports())[i].c_str(), &this->hints, &this->res);
        if (getaddrinfo_status != 0)
            EXTMSG(gai_strerror(getaddrinfo_status));
        for (struct addrinfo* rp = this->res; rp != NULL; rp = rp->ai_next)
        {
            fd_sock = socket(rp->ai_family, rp->ai_socktype, rp->ai_protocol);
            if (fd_sock == -1)
                continue ;
            if (bind(fd_sock, rp->ai_addr, rp->ai_addrlen) == 0)
            {
                BIND_STATUS = 1;
                break ;
            }
            close(fd_sock);
        }
        
        freeaddrinfo(this->res);
        if (BIND_STATUS == 0)
            EXTMSG("bind failed"); 
        if (listen(fd_sock, MAX_QUEUE) < 0)
            EXTMSG("listen failed");
        std::cout << fd_sock << " socket is pushed\n";
        this->set_Socket(fd_sock);
    }
 
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