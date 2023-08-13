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
        std::cout << "nember event is : " << n_event << std::endl;
        for (int i = 0; i < n_event; i++)
        {
            struct kevent * curr = &this->event[i];
            if (curr->flags & EV_ERROR)
            {
                std::cout << "client disconnected : " << curr->ident << " end of file\n";
                this->delete_event(curr->ident, EVFILT_READ);
            }
            else if (Global().is_server_sock(curr->ident))
            {
                __network& net = Global().network(curr->ident);
                int client = net.accept_new_client(curr->ident, net.get_server());
                std::cout << "server have request from client : " << client << std::endl;
                this->add_event(client, EVFILT_READ);
            }
            else if (Global().is_client_sock(curr->ident))
            {
                if (curr->filter == EVFILT_READ)
                {
                    // request here
                    std::cout << "request from client : " << curr->ident << std::endl;
                    this->delete_event(curr->ident, EVFILT_READ);// delete read from client.
                    this->add_event(curr->ident, EVFILT_WRITE);
                }
                else
                {
                    // response here
                    // client ready to write data to the browser.
                    std::cout << "i send something here and i close this client after finish sending\n";
                    this->delete_event(curr->ident, EVFILT_WRITE);
                    close(curr->ident);
                }
            }
        }
    }
}