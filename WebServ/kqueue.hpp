#ifndef __KQUEUE_HPP__
#define __KQUEUE_HPP__
#include <sys/event.h>
#include <sys/time.h>
#include <netinet/in.h>
#include <fcntl.h>

#define MAX_SIMULTANEOUS 2048

typedef struct _kqueue {
    // variables
    int fd;
    struct kevent change;
    struct kevent event[MAX_SIMULTANEOUS];
    
    // methods


} _kqueue;


#endif