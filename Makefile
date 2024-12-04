NAME := ircserv

SRCS := \
	Channel/Channel.cpp \
	Client/Client.cpp \
	Server/Server.cpp \
	main.cpp \
	Commands/Nick.cpp \
	Commands/Pass.cpp \
	Commands/User.cpp \
	Commands/Join.cpp \
	Commands/Privmsg.cpp \
	Commands/Who.cpp \
	Commands/Kick.cpp \
	Commands/Part.cpp \
	Commands/Topic.cpp \
	Commands/Quit.cpp \
	Commands/Notice.cpp \
	Commands/Mode.cpp

OBJS := $(SRCS:.cpp=.o)
CXX := c++
CXXFLAGS := -g -Wall -Wextra -Werror -std=c++98

.PHONY: all clean fclean re

all: $(NAME)

$(NAME): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $^

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME)

re: fclean all
