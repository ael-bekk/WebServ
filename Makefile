NAME	= serv

SRCS	= Info/info.cpp WebServ/webserv.cpp Network/network.cpp Server/server.cpp Location/location.cpp Request/request.cpp Response/response.cpp Client/client.cpp  test_config.cpp \
			 Select/select.cpp Epoll/epoll.cpp Post/post.cpp

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