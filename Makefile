NAME = ircserv

CXX = clang++

CXXFLAGS = -Wall -Wextra -Werror -std=c++98 -I .

SRC =	main \
		utils \
		server \
		handle_commands \
		commands/die \
		commands/invite \
		commands/join \
		commands/kick \
		commands/kill \
		commands/list \
		commands/names \
		commands/nick \
		commands/oper \
		commands/part \
		commands/pass \
		commands/privmsg \
		commands/topic \
		commands/user \
		commands/who \
		commands/quit

FIL = $(addsuffix .cpp, $(SRC))

OBJ = $(FIL:.cpp=.o)

BIN = $(addsuffix .o, $(SRC))

.PHONY: all clean fclean re

all: $(NAME)

$(NAME): $(OBJ)
	$(CXX) -o $(NAME) $(OBJ)

clean:
	rm -rf $(OBJ)

fclean: clean
	rm -rf $(NAME)

re: fclean all
