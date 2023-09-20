#include "server.hpp"
#include "../Info/info.hpp"

__server::__server(int &line_count, std::ifstream &configfile) {
    std::string line, key;

    while (std::getline(configfile, line) && ++line_count) {
        std::stringstream test_inp(line);
        std::string test_;
        if NOT_EMPTY()
        {
            std::stringstream inp(line);

            inp >> key;
            if (IS_EXIT(key)) break;
            if (!Insert(key, line_count, configfile, inp) || inp >> line)
                ConfigError(line_count, key);
        }
    }
    
    Global().add_server(this->host, this->port, this->server_name, this);
}

__server::~__server() {}

bool __server::Insert(std::string key, int &line_count, std::ifstream &configfile, std::stringstream &inp) {

    int ret = FAILURE;
    std::string val, val2;

    if (IS_HOST(key) && inp >> val)
        ret = set_host(val);
    else if (IS_PORT(key) && inp >> val)
        ret = set_port(val);
    else if (IS_SERVER_NAME(key) && inp >> val)
        ret = set_server_name(val);
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

std::string __server::get_host()                                { return this->host; }
std::string __server::get_port()                                { return this->port; }
std::string __server::get_server_name()                         { return this->server_name; }
std::map<std::string, std::string> __server::get_error_pages()  { return this->error_page; }
unsigned long long __server::get_client_max_body_size()         { return this->client_max_body_size; }
std::map<std::string, __location> __server::get_locations()     { return this->location; }

int __server::set_host(std::string host) {
    std::stringstream inp(host);
    std::string slice;
    int count = 0;

    if (host == "localhost")
        this->host = LOCALE_HOST;
    else {
        while (std::getline(inp, slice, '.') && ++count){
            try {
                int value = std::atoi(slice.c_str());
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

int __server::set_port(std::string port) {
    if (!this->port.empty())
        return FAILURE;
    this->port = port;
    return SUCCESS;
}

int __server::set_server_name(std::string server_name) {
    this->server_name = server_name;
    return SUCCESS;
}

int __server::set_error_pages(std::string error, std::string page) {
    this->error_page[error] = page;
    return SUCCESS;
}

int __server::set_client_max_body_size(std::string client_max_body_size) {
    if (client_max_body_size.length() > 14)
        return FAILURE;

    this->client_max_body_size = std::atoll(client_max_body_size.c_str());
    return SUCCESS;
}

int __server::set_locations(int &line, std::ifstream &configfile, std::stringstream &inp) {
    std::string end, token, path;
    if (!(inp >> token) || !(inp >> end) || !IS_ENTER(end) || inp >> end)
        return FAILURE;
    
    CLEAR_LOCATION_PATH()

    if (this->location.find(path) != this->location.end())
        throw std::string("Location duplicated hah");

    this->location.insert(std::pair<std::string, __location>(path, __location(line, configfile)));
    return SUCCESS;
}