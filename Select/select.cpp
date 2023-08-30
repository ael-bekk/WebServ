#include "select.hpp"
#include "../Info/info.hpp"

// void _select::ForEach() {

// }

void    _select::set_zero() {
    FD_ZERO(&this->readable);
    FD_ZERO(&this->writable);
}

 void    _select::set_fd(int sock) {
    FD_SET(sock, &this->readable);
    FD_SET(sock, &this->writable);
}

short   _select::CloseClient(int sock) {
    
    Global().rm_client(sock);
    if (close(sock) == -1) {
        std::cerr << "close() error!\n";
        exit(1);
    }
    
    std::cout << "C : " << sock << std::endl;
    return SUCCESS;
}

#include <signal.h>

void _select::CheckSockStatus(int sock, int status) {
    if (METHOD_POST_TRANSFER_NOT_SUPPORTED == status)
        FD_CLR(sock, &readable),
        FD_CLR(sock, &writable),
        this->CloseClient(sock);
    if IS_SOCK_CLOSED(status)
        FD_CLR(sock, &readable),
        FD_CLR(sock, &writable),
        this->CloseClient(sock);
    if IS_SOCK_END_REQUEST(status)
        FD_CLR(sock, &readable),
        FD_SET(sock, &writable);
    if IS_SOCK_END_RESPONSE(status)
        FD_CLR(sock, &readable),
        FD_CLR(sock, &writable),
        this->CloseClient(sock);
}

void _select::multiplexing() {

    int client_sock;
    timeout.tv_usec = 500;
    timeout.tv_sec = 0;
    signal(SIGPIPE, SIG_IGN);
    while (true) {
        FD_ZERO(&this->r);
        FD_ZERO(&this->w);
        this->r = readable;
        this->w = writable;

        if (!select(Global().max_sock() + 1, &this->r, &this->w, 0, &this->timeout))
            continue;

        for (int i = 0; i <= Global().max_sock(); i++)
            if (Global().is_server_sock(i) && FD_ISSET(i, &this->r)) {
                __network & net = Global().network(i);
                std::cout << "E : ";
                client_sock = net.accept_new_client(i);

                std::cout << client_sock << std::endl;
                FD_SET(client_sock, &readable);
            } else if (Global().is_client_sock(i)) {
                __client & client = Global().client(i);
                int status = 0;

                FD_ISSET(i, &this->r) && (status = client.Receive());
                FD_ISSET(i, &this->w) && (status = client.Send());

                CheckSockStatus(i, status);
            }
    }
}