NAME = nibbler_ncurses.so

SRC = NcurseGraphics.cpp

OBJ = $(SRC:.cpp=.o)

FLAGS = -Wall -Wextra -Werror -std=c++14 -fPIC

LIBFLAGS = -shared -fPIC -lncurses

CC = clang++

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(FLAGS) $(LIBFLAGS) -o $(NAME) $(OBJ)

%.o: %.cpp
	$(CC) $(FLAGS) -o $@ -c $<

clean:
	@rm -rf $(OBJ)

fclean: clean
	@rm -rf $(NAME)

re: fclean all
