#ifndef __STDC_HPP__
#define __STDC_HPP__

/*                    ►   files tree   ◄            

├► bits     ⤵
|           ├⟚ stdc++.hpp
|
|
├► WebServ  ⤵
|           ├⟚ webserv.hpp
|           ├⟚ webserv.cpp
|           ├► Network   ⤵
|                        ├⟚ network.hpp
|                        ├⟚ network.cpp
|                        ├► Client   ⤵
|                        |           ├⟚ client.hpp
|                        |           ├⟚ client.cpp
|                        |           ├► Request  ⤵
|                        |           |           ├⟚ request.hpp
|                        |           |           ├⟚ request.cpp
|                        |           |
|                        |           |
|                        |           ├► Response ⤵
|                        |                       ├⟚ response.hpp
|                        |                       ├⟚ response.cpp
|                        |                       ├► Get     ⤵
|                        |                       |          ├⟚ get.hpp
|                        |                       |          ├⟚ get.cpp
|                        |                       |
|                        |                       |
|                        |                       ├► Post    ⤵
|                        |                       |          ├⟚ post.hpp
|                        |                       |          ├⟚ post.cpp
|                        |                       |
|                        |                       |
|                        |                       ├► Delete ⤵
|                        |                                  ├⟚ delete.hpp
|                        |                                  ├⟚ delete.cpp
|                        |
|                        |
|                        ├► Server  ⤵
|                                    ├⟚ server.hpp
|                                    ├⟚ server.cpp 
|                                    ├► Location ⤵
|                                                ├⟚ location.hpp
|                                                ├⟚ location.cpp

*/

#include <algorithm>
#include <bitset>
#include <complex>
#include <deque>
#include <exception>
#include <fstream>
#include <functional>
#include <iomanip>
#include <ios>
#include <iosfwd>
#include <iostream>
#include <iterator>
#include <limits>
#include <list>
#include <locale>
#include <map>
#include <memory>
#include <new>
#include <numeric>
#include <ostream>
#include <queue>
#include <set>
#include <sstream>
#include <stack>
#include <stdexcept>
#include <streambuf>
#include <string>
#include <typeinfo>
#include <utility>
#include <valarray>
#include <vector>

<<<<<<< HEAD
#include <sys/event.h>
#include <sys/time.h>
#include <netinet/in.h>
#include <fcntl.h>

#include <netdb.h>      // header file for network-related functions and structures (e.g., getaddrinfo)
#include <netinet/in.h> // header file for internet protocol-related functions and structures (e.g., sockaddr_in)
#include <sys/socket.h> // header file for socket programming functions and structures (e.g., socket, bind, listen, accept)
#include <arpa/inet.h>  // header file for internet protocol-related functions (e.g., inet_addr, inet_ntoa)
#include <string.h> // for using memset
#include <unistd.h> // for using close();
#include <arpa/inet.h> // to test inet_ntoa() function 
=======
//kqueue things
#include <sys/types.h>
#include <sys/event.h>
#include <sys/time.h>
>>>>>>> 6d98c2da143e14fd6e3c48124b8f382f7f2bf0d7

#include "define.hpp"



#endif