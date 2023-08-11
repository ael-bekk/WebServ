#include "select.hpp"

// void _select::ForEach() {

// }

void _select::multiplexing() {
    
    int clnt_sock;
    Global().max_sock();

    FD_ZERO(&readable);
    FD_ZERO(&writable);

    for (int i = 0; i < Global().max_sock(); i++)
        if (Global().is_server_sock(i)) {
            FD_SET(i, &readable);
            FD_SET(i, &writable);
        }

    while (true) {
        r = readable;
        w = writable;

        if (!select(Global().max_sock() + 1, &readable, &writable, 0, NULL))
            continue;

        for (int i = 0; i <= Global().max_sock(); i++) {
            if (Global().is_server_sock(i) && FD_ISSET(i, &readable)) {
                __network & net = Global().network(i);
                clnt_sock = net.accept_new_client(i, net.get_server());
                FD_SET(clnt_sock, &readable);
                FD_SET(clnt_sock, &writable);
                std::cout << "wa njh" << std::endl;
            } else if (Global().is_client_sock(i)) {
                if (FD_ISSET(i, &readable)) {
                    
                } else if (FD_ISSET(i, &writable)) {

                }
            }
        }
    }
}