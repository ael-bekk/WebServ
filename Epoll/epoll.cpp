#include "epoll.hpp"

void    _epoll::add_event(uint32_t flags ,int sock)
{
    this->ev.events = flags;
    this->ev.data.fd = sock;
    if (epoll_ctl(this->fd, EPOLL_CTL_ADD, sock, &this->ev) == -1)
        EXTMSG("epoll_ctl failed ");
    
}
void    _epoll::delete_event(uint32_t flags ,int sock)
{
    this->ev.events = flags;
    this->ev.data.fd = sock;
    if (epoll_ctl(this->fd, EPOLL_CTL_DEL, sock, &this->ev) == -1)
        EXTMSG("epoll_ctl failed ");
}

void    _epoll::instance()
{
    this->fd = epoll_create(MAX_QUEUE);
    if (this->fd == -1)
        EXTMSG("epoll create failed ");
}

// this is test functions , we will remove it after you prepare request.

void    _epoll::advanced_send_video(std::pair<int, std::pair<int, bool> >& pr)
{

    int client_fd = pr.first;
    if (pr.second.first == -1)
        return ;
    std::cout << "i will read from ==> " << pr.second.first << std::endl;

    char buff[1024];
    int rd = read(pr.second.first, buff, 1024);
    if (rd == -1)
    {
        std::cout << "client that request the video is " << client_fd << std::endl;
        perror("error reading video \n");
        delete_event(EPOLLIN | EPOLLOUT, client_fd);
        close (client_fd);
        close (pr.second.first);
        pr.second.first = -1;
    }
    if (rd == 0)
    {
        std::cout << "there is nothing to read from the video\n";
        delete_event(EPOLLIN | EPOLLOUT, client_fd);
        close (client_fd);
        close (pr.second.first);
        pr.second.first = -1;
    }
    else if (send(client_fd, buff, rd, 0) < 0 )
    {
        perror("error sending video\n");
        delete_event(EPOLLIN | EPOLLOUT, client_fd);
        close (client_fd);
        close (pr.second.first);
        pr.second.first = -1;
    }
}

void    _epoll::send_header(std::pair<int, std::pair<int, bool> >& pr)
{

    if (pr.second.first == 0)
        return ;
    std::cout << "Data of header is ==> " <<  pr.first << " " << pr.second.first << std::endl;
    int vid_fd = pr.second.first;
    int client_fd = pr.first;
    off_t size = lseek(vid_fd, 0, SEEK_END);
    lseek(vid_fd, 0, SEEK_SET);

    
    char header[1024];
    sprintf(header, "HTTP/1.1 200 OK\r\nContent-Type: video/mp4\r\nContent-Length: %ld\r\n\r\n", size);
    int sd = send(client_fd, header, strlen(header), 0);
    if (!sd || sd == -1)
    {
        perror("error send header \n");
        exit(errno);
    }
    pr.second.second = 1;
}

void    _epoll::receive_header(int fd)
{
    char buff[1024];
    int rd = read(fd, buff, 1024);
    if (rd <= 0)
    {
        std::cout << "there is nothing to read from header\n";
        delete_event(EPOLLIN | EPOLLOUT, fd);
        close(fd);
    }
    std::cout << buff << std::endl;
}

// end of test fucntions


void    _epoll::Epoll()
{
    this->client.resize(1000);

    while (true)
    {
        int n_event = epoll_wait(this->fd, this->change, MAX_QUEUE, -1);
        if (n_event == -1)
            EXTMSG("epoll_wait failed ");
        std::cout << "number event is : " << n_event << std::endl;
        for(int i = 0; i < n_event; i++)
        {
            struct epoll_event* curr = &change[i];
            if (curr->events & EPOLLERR)
            {
                std::cout << "EVENT EPOLLER HAPPEN\n";
                delete_event(EPOLLIN | EPOLLOUT, curr->data.fd);
                close(curr->data.fd);
                close(client[curr->data.fd].second.first);
                client[curr->data.fd].second.first = -1;
            }
            else if (Global().is_server_sock(curr->data.fd))
            {
                __network& net = Global().network(curr->data.fd);
                int clt_sock = net.accept_new_client(curr->data.fd);
                this->add_event(EPOLLIN | EPOLLOUT, clt_sock);
                std::cout << "client connected : " << clt_sock << std::endl;
            }
            else if (Global().is_client_sock(curr->data.fd))
            {
                if (curr->events & EPOLLIN)
                {
                    // this is request place
                    //this is test
                    receive_header(curr->data.fd);
                    int vid_fd = open("animated.mp4", O_RDONLY);
                    if (vid_fd == -1)
                    {
                        perror("error on opening the video \n");
                        exit(errno);
                    }
                    int cl = curr->data.fd;
                    client[curr->data.fd] = (std::make_pair(cl, std::make_pair(vid_fd, 0)));

                }
                else if (curr->events & EPOLLOUT)
                {
                    // this is response place

                    // this is test
                    int check = client[curr->data.fd].second.second;

                    if (check == 0)
                        send_header(client[curr->data.fd]);
                    else
                        advanced_send_video(client[curr->data.fd]);
                }
            }
        }
    }
}