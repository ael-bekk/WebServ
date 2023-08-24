#ifndef __SELECT_HPP__
#define __SELECT_HPP__

#include "../bits/stdc++.hpp"

typedef struct _select {
    fd_set                      r;
    fd_set                      w;
    fd_set                      readable;
    fd_set                      writable;
    struct timeval              timeout;

    short    CloseClient(int sock);
    void    CheckSockStatus(int sock, int status);
    void    multiplexing();
    void    set_zero();
    void    set_fd(int sock);
}   _select;

#endif