#include "client.hpp"
#include "../Info/info.hpp"

__client::__client(int sock, std::string host, std::string port, __server *server) : socket(sock), server(server), host(host), port(port) {
    request = new __request(sock);
    response = new __response(sock);
}

__client::~__client() {
    delete this->server;
    delete this->request;
    delete this->response;
}

size_t __client::get_socket()       { return this->socket; }
__server *__client::get_server()     { return this->server; }
std::string __client::get_host()    { return this->host; }
std::string __client::get_port()    { return this->port; }

void    __client::MatchLocation() {
    std::string actual_path, tmp_path, path, req_path;

    tmp_path = Global().get_RequestHeader(this->socket, "Path");
    CLEAR_REQUEST_PATH()
    req_path = path;
    std::map<std::string, __location> loc = this->server->get_locations();
    FIND_LOCATION_FROM_PATH()
    // std::cout << "------>" << path << " " << (loc.find("/") != loc.end()) << std::endl;
    std::map<std::string, __location>::iterator it = loc.find(path.empty() ? "/" : path);

    if (it != loc.end())
        LOCATION_FOUND()
}

void __client::set_server(__server *server)  {
    this->server = server;
    this->MatchLocation();
}

short    __client::Receive() { return this->request->Rqst();}
short    __client::Send()    { return this->response->Rspns();}