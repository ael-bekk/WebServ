#include "server.hpp"

__server::__server(int &line_count, std::ifstream &configfile) {
    std::string line, key;

    while (std::getline(configfile, line) && ++line_count) {
        std::stringstream inp(line);

        inp >> key;
        if (IS_EXIT(key)) break;
        if (!Insert(key, line_count, configfile, inp) || inp >> line)
            ConfigError(line_count, key);
    }
}

__server::~__server() {}

bool __server::Insert(std::string key, int &line_count, std::ifstream &configfile, std::stringstream &inp) {

    int ret = FAILURE;
    std::string val, val2;

    if (IS_HOST(key) && inp >> val)
        ret = set_host(val);
    else if (IS_PORT(key) && inp >> val)
        ret = set_ports(val);
    else if (IS_ERROR_PAGE(key) && inp >> val && inp >> val2)
        ret = set_error_pages(val, val2);
    else if (IS_CLIENT_MAX_BODY_SIZE(key) && inp >> val)
        ret = set_client_max_body_size(val);
    else if (IS_LOCATION(key))
        ret = set_locations(line_count, configfile, inp);
    return ret;
}

void    __server::ConfigError(int line, std::string detail) {
    std::cout << "Error : line=" << line << " in the server block ==> \"" << detail << "\"" << std::endl;
    exit(1);
}

std::string __server::get_host()                        { return this->host; }
std::vector<std::string> __server::get_ports()       { return this->port; }
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
        while (std::getline(inp, slice, '.') && ++count){
            try {
                int value = std::stoi(slice);
                if (value < 0 || value > 255)
                    return FAILURE;
            } catch (const std::invalid_argument& e) {
                // Handle the case when the slice is not a valid integer.
                return FAILURE;
            }
        }
        if (count != 4) return FAILURE;
        this->host = host;
    }
    return SUCCESS;
}

int __server::set_ports(std::string port) {
    this->port.push_back(port);
    return SUCCESS;
}

int __server::set_error_pages(std::string error, std::string page) {
    this->error_page[std::stoi(error)] = page;
    return SUCCESS;
}

int __server::set_client_max_body_size(std::string client_max_body_size) {
    this->client_max_body_size = std::stoi(client_max_body_size);
    return SUCCESS;
}

int __server::set_locations(int &line, std::ifstream &configfile, std::stringstream &inp) {
    this->location.push_back(__location(line, configfile, inp));
    return SUCCESS;
}