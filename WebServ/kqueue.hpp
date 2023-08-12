#ifndef __KQUEUE_HPP__
#define __KQUEUE_HPP__

#include "../bits/stdc++.hpp"
#include "../Info/info.hpp"

typedef struct _kqueue {
    // variables
    int fd;
    struct kevent change;
    struct kevent event[MAX_QUEUE];
    
    // methods
        void    add_event(int newfd, int16_t filter);
        void    delete_event(int newfd, int16_t filter);
        void    kQueue();
        void    CreateKqueue();

} _kqueue;


#endif