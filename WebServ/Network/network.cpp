#include "network.hpp"

__network::__network(std::istream &configfile) : server(configfile) {}

__network::~__network() {}