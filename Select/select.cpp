#include "select.hpp"
#include "../Info/info.hpp"

// void _select::ForEach() {

// }

short   _select::CloseClient(int sock) {
    
    Global().rm_client(sock);
    if (close(sock)) {
        std::cerr << "close() error!\n";
        exit(1);
    }
    
    std::cout << "C : " << sock << std::endl;
    return SUCCESS;
}

#include <signal.h>

void _select::CheckSockStatus(int sock, int status) {
    if (IS_SOCK_CLOSED(status))
        this->CloseClient(sock);
    if (IS_SOCK_END_REQUEST(status))
        FD_CLR(sock, &readable),
        FD_SET(sock, &writable);
    if (IS_SOCK_END_RESPONSE(status))
        FD_CLR(sock, &writable),
        this->CloseClient(sock);
}

void _select::multiplexing() {

    int client_sock;

    signal(SIGPIPE, SIG_IGN);
    while (true) {
        r = readable;
        w = writable;

        if (!select(Global().max_sock() + 1, &r, &w, 0, &this->timeout))
            continue;

        for (int i = 0; i <= Global().max_sock(); i++) {
            if (Global().is_server_sock(i) && FD_ISSET(i, &r)) {
                __network & net = Global().network(i);
                client_sock = net.accept_new_client(i);
                FD_SET(client_sock, &readable);
            } else if (Global().is_client_sock(i)) {
                __client & client = Global().client(i);
                int status = 0;

                FD_ISSET(i, &r) && (status = client.Receive());
                FD_ISSET(i, &w) && (status = client.Send());

                CheckSockStatus(i, status);
            }
        }
    }
}