NAME	= serv

SRCS	= WebServ/webserv.cpp WebServ/Network/network.cpp WebServ/Network/Server/server.cpp WebServ/Network/Server/Location/location.cpp WebServ/Network/Client/client.cpp WebServ/Network/Client/Request/request.cpp WebServ/Network/Client/Response/response.cpp test_config.cpp \
			Info/info.cpp WebServ/select.cpp

CFLAGS	= 

CC		= c++ -std=c++11

RM		= rm -fr

all:		$(NAME)

$(NAME):	$(SRCS)
	$(CC) $(CFLAGS) $(SRCS) -o $(NAME)

clean:
	$(RM) $(NAME)

re:			clean all

.PHONY:		all clean re