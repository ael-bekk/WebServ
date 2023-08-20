#include "select.hpp"

// void _select::ForEach() {

// }

bool    _select::CloseClient() {
    
    return SUCCESS;
}

void _select::multiplexing() {

    int clnt_sock;

    while (true) {
        r = readable;
        w = writable;

        if (!select(Global().max_sock() + 1, &r, &w, 0, NULL))
            continue;

        for (int i = 0; i <= Global().max_sock(); i++) {
            if (Global().is_server_sock(i) && FD_ISSET(i, &r)) {
                __network & net = Global().network(i);
                clnt_sock = net.accept_new_client(i);
                FD_SET(clnt_sock, &readable);
                FD_SET(clnt_sock, &writable);
                std::cout << "wa njh" << std::endl;
            } else if (Global().is_client_sock(i)) {
                __client & clnt = Global().client(i);
                if (FD_ISSET(i, &r)) {
                    FAIL(clnt.Receive()) && _select::CloseClient();
                } else if (FD_ISSET(i, &w))
                    FAIL(clnt.Send()) && _select::CloseClient();
            }
        }
    }
}