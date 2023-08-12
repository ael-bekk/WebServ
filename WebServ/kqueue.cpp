#include "kqueue.hpp"

void    _kqueue::add_event(int newfd, int16_t filter)
{
    EV_SET(&this->change, newfd, filter, EV_ADD | EV_ENABLE , 0, 0, 0);
    kevent(this->fd, &this->change, 1, NULL, 0, NULL);
}
void    _kqueue::delete_event(int newfd, int16_t filter)
{
    EV_SET(&this->change, newfd, filter, EV_DELETE | EV_CLEAR , 0, 0, 0);
    kevent(this->fd, &this->change, 1, NULL, 0, NULL);
}

void    _kqueue::CreateKqueue()
{
    this->fd = kqueue();
    if (this->fd == -1)
        EXTMSG("kqueue failed");
}

void    _kqueue::kQueue()
{
    while (1)
    {
        int n_event = kevent(this->fd, NULL, 0, this->event, 1, NULL);
        for (int i = 0; i < n_event; i++)
        {
            struct kevent * curr = &this->event[i];
            if (curr->flags & EV_ERROR)
            {
                std::cout << "client disconnected : " << curr->ident << " end of file\n";
                delete_event(curr->ident, EVFILT_READ);
            }
            else if (Global().is_server_sock(curr->ident))
            {
                __network& net = Global().network(curr->ident);
                net.accept_new_client(curr->ident, net.get_server());
                std::cout << "server have request\n";
            }
        }
    }
}