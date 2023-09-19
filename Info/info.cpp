#include "info.hpp"

__info::__info() : _max(0) {
    this->set_all_icons();
}

__info& __info::Instance()
{
    static __info INSTANCE;
    return INSTANCE;
}

void __info::update_sock(int fd) {
    this->_max = std::max(this->_max, fd);
}

void __info::add_server_sock(int fd) {
    this->server_sockets[fd] = true;
}

void __info::add_network(int fd, __network & net) {
    this->server_sockets[fd] = true;
    this->networks.insert(std::pair<__network*, int>(&net, fd));
}

void __info::add_client(int fd, std::string host, std::string port, __server *serv) {
    this->client_sockets[fd] = true;
    this->clients.insert(std::pair<int, __client*>(fd, new __client(fd, host, port, serv)));
}

void __info::rm_client(int fd) {
    this->client_sockets[fd] = false;
    delete this->clients[fd];
    this->RequestHeader.erase(fd);
    this->ResponseHeader.erase(fd);
    this->clients.erase(fd);
}

void __info::add_RequestHeader(int fd, std::string key, std::string value) {
    this->RequestHeader[fd][key] = value;
}

void __info::add_ResponseHeader(int fd, std::string key, std::string value) {
    this->ResponseHeader[fd][key] = value;
}

void __info::add_server(std::string host, std::string port, std::string server_name, __server * serv) {
    if (this->servers[host + ":" + port + ":" + server_name] == NULL)
        this->servers[host + ":" + port + ":" + server_name] = serv;
    else
        EXTMSG("Detected duplicate servers : host;port;server_name")
    if (this->servers[host + ":" + port] == NULL)
        this->servers[host + ":" + port] = serv;
}

void __info::set_MimeTypes() {
    std::ifstream   mime_file(MIMETYPESFILE);
    std::string     line;
    std::string     m1, m2;

    if (mime_file.fail())
        EXTMSG("Error opening file: mime.types.txt")

    while (std::getline(mime_file, line))
        if NOT_EMPTY()
        {
            std::stringstream inp(line);
            if (!(inp >> m1 >> m2))
                EXTMSG("Error parsing file: mime.types.txt")
            this->ClientMimeTypes[m2] = m1;
            this->ServerMimeTypes[m1] = m2;
            while (inp >> m2)
                this->ClientMimeTypes[m2] = m1;
        }
}

void __info::set_all_icons() {
    this->icons["c++"]  = this->icons["cpp"]  = this->icons["css"] = true;
    this->icons["html"] = this->icons["jpeg"] = this->icons["jpg"] = true;
    this->icons["js"]   = this->icons["mp4"]  = this->icons["pdf"] = true;
    this->icons["php"]  = this->icons["png"]  = this->icons["py"]  = true;
    this->icons["scss"] = this->icons["ico"]  = true;
}


bool __info::check_icon(std::string key) {
    return this->icons[key];
}

int __info::max_sock() {
    return this->_max;
}

bool __info::is_server_sock(int fd) {
    return this->server_sockets[fd];
}

__network&  __info::network(int fd) {
    
    for (std::map<__network *, int>::iterator i = this->networks.begin(); i != this->networks.end(); i++)
        if (i->second == fd)
            return *i->first;
    return *this->networks.begin()->first;
}


bool __info::is_client_sock(int fd) {
    return this->client_sockets[fd];
}

__client&  __info::client(int fd) {
    return *this->clients[fd];
}

__info& Global() { return __info::Instance(); }

std::string __info::get_RequestHeader(int fd, std::string key) {
    return this->RequestHeader[fd][key];
}

std::string __info::get_ResponseHeader(int fd, std::string key) {
    return this->ResponseHeader[fd][key];
}

__server * __info::get_server(std::string host, std::string port, std::string server_name) {
    if (this->servers[host + ":" + port + ":" + server_name] != NULL)
        return this->servers[host + ":" + port + ":" + server_name];
    return this->servers[host + ":" + port];
}

std::string __info::get_ClientMimeTypes(std::string key) {
    return this->ClientMimeTypes[key];
}

std::string __info::get_ServerMimeTypes(std::string key) {
    return this->ServerMimeTypes[key];
}


__info::~__info() {
    // for (std::map<__network *, int>::iterator i = this->networks.begin(); i != this->networks.end(); i++)
    //     delete i->first;
    for (std::map<int, __client *>::iterator i = this->clients.begin(); i != this->clients.end(); i++)
        delete i->second;
    for (std::map<std::string, __server * >::iterator i = this->servers.begin(); i != this->servers.end(); i++)
        delete i->second;
}