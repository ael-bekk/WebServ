#ifndef __EPOLL_HPP__
#define __EPOLL_HPP__

#include "../bits/stdc++.hpp"
#include <sys/epoll.h>


typedef struct _epoll{
    
    //variabls 
    int fd;
    struct epoll_event ev;
    struct epoll_event change[MAX_QUEUE];

    //methods
    void    add_event(uint32_t flags ,int sock);
    void    delete_event(uint32_t flags ,int sock);
    void    instance();
    void    Epoll();

    // test function & variables
    std::vector<std::pair<int, std::pair<int, bool> > > client;
    void    receive_header(int fd);
    void    send_header(std::pair<int, std::pair<int, bool> >& pr);
    void    advanced_send_video(std::pair<int, std::pair<int, bool> >& pr);
} _epoll;


#endif