#ifndef __KQUEUE_HPP__
#define __KQUEUE_HPP__

#include "../bits/stdc++.hpp"

typedef struct _kqueue {
    // variables
    int fd;
    struct kevent change;
    struct kevent event[MAX_SIMULTANEOUS];

    // methods


} _kqueue;


#endif