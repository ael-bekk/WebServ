#include "select.hpp"
#include "../Info/info.hpp"

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
        // std::cerr << "close() error!\n";
        exit(1);
    }
    if (!Global().tmp_file[sock].empty()) {
        remove(Global().tmp_file[sock].c_str());
        Global().tmp_file.erase(sock);
    }
    if (!Global().tmp_file[-sock].empty()) {
        remove(Global().tmp_file[-sock].c_str());
        Global().tmp_file.erase(-sock);
    }
    Global().exec_cgi.erase(sock);
    std::cout << URed << sock << " : " << "↪️ Exit" << Color_Off << std::endl;
    return SUCCESS;
}

#include <signal.h>

void _select::CheckSockStatus(int sock, int status) {
    if IS_SOCK_CLOSED(status) {
        FD_CLR(sock, &readable);
        FD_CLR(sock, &writable);
        this->CloseClient(sock);
    }
    if IS_SOCK_END_REQUEST(status) {
        FD_CLR(sock, &readable);
        FD_SET(sock, &writable);
    }
    if IS_SOCK_END_REQUEST_MAX_SIZE(status) {
        Global().add_ResponseHeader(sock, "status", HTTP_413_PAYLOAD_TOO_LARGE);
        FD_CLR(sock, &readable);
        FD_SET(sock, &writable);
    }
    if IS_SOCK_END_RESPONSE(status) {
        FD_CLR(sock, &writable);
        this->CloseClient(sock);
    }
}

void _select::multiplexing() {

    int client_sock;
    srand(time(NULL));
    timeout.tv_usec = 500;
    timeout.tv_sec = 0;
    signal(SIGPIPE, SIG_IGN);

    while (true) {
        this->r = readable;
        this->w = writable;

        if (!select(Global().max_sock() + 1, &this->r, &this->w, 0, &this->timeout))
            continue;

        for (int socket = 0; socket <= Global().max_sock(); socket++)
            if (Global().is_server_sock(socket) && FD_ISSET(socket, &this->r)) {
                __network & net = Global().network(socket);
                client_sock = net.accept_new_client(socket);

                std::cout << UGreen << client_sock << " : " << "↩️ Enter" << Color_Off << std::endl;
                FD_SET(client_sock, &readable);
            } else if (Global().is_client_sock(socket)) {
                __client & client = Global().client(socket);
                int status = 0;
                
                FD_ISSET(socket, &this->r) && (status = client.Receive());
                FD_ISSET(socket, &this->w) && (status = client.Send());

                CheckSockStatus(socket, status);
            }
    }
}