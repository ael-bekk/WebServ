#include "server.hpp"

__server::__server(int &line_count, std::istream &configfile) {
    std::string line, key, val;

    set_default();
    while (std::getline(configfile, line) && ++line_count) {
        std::stringstream inp(line);

        inp >> key;
        if (IS_EXIT(key)) break;
        if (!(inp >> val) || !_insert(key, val, configfile) || inp >> val)
            ConfigError(line_count, key);
    }
}

__server::~__server() {}

bool __server::_insert(std::string key, std::string val, std::istream &configfile, std::stringstream &inp) {

    int ret = FAILURE;
    std::string val2;

    if (IS_HOST(key))
        ret = set_host(val);
    else if (IS_PORT(key))
        ret = set_ports(val);
    else if (IS_ERROR_PAGE(key) && inp >> val2)
        ret = set_error_pages(val, val2);
    else if (IS_CLIENT_MAX_BODY_SIZE(key))
        ret = set_client_max_body_size(val);
    else if (IS_LOCATION(key))
        ret = set_locations(configfile);

    return ret;
}

void __server::set_default() {
    this->error_page = default_err_page;
    this->client_max_body_size = DEFAULT_MAX_BODY_SIZE;
    this->host = LOCALE_HOST;
    this->port = DEFAULT_PORT;
}

void    ConfigError(int line, std::string detail) {
    cout << "Error : line=" << line << " in the server block ==> \"" << detail << "\"" << std::endl;
    exit();
}

std::string __server::get_host()                        { return this->host; }
std::vector<unsigned short> __server::get_ports()       { return this->port; }
std::map<int, std::string> __server::get_error_pages()  { return this->error_page; }
size_t __server::get_client_max_body_size()             { return this->client_max_body_size; }
std::vector<__location> __server::get_locations()       { return this->location; }

int __server::set_host(std::string host) {
    std::stringstream inp(host);
    std::string slice;
    int count = 0;

    if (host == "localhost")
        this->host = LOCALE_HOST;
    else {
        while (std::getline(inp, slice, ".") && ++count)
            if (stoi(slice) < 0 || stoi(slice) > 255) return FAILURE;
        if (count != 4) return FAILURE;
        this->host = host;
    }
    return SUCCESS;
}

int __server::set_ports(std::string port) {
    if (port.length() > 4)
        return FAILURE;
    this->port.push_back(port);
    return SUCCESS;
}

int __server::set_error_pages(std::string error, std::string page) {
    this->error_page[stoi(error)] = page;
    return SUCCESS;
}

int __server::set_client_max_body_size(std::string client_max_body_size) {
    this->client_max_body_size = stoi(client_max_body_size);
    return SUCCESS;
}

int __server::set_locations(int &line, std::istream &configfile) {
    this->location.push_back(__location(line, configfile));
    return SUCCESS;
}