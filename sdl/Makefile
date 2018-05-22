NAME = nibbler_sdl.so

C_DIR =	src
C_FILES = src/SDLGraphicLib.cpp

O_DIR =	.tmp/obj
O_FILES = $(C_FILES:$(C_DIR)%.cpp=$(O_DIR)%.o)

FLAGS = -Wall -Wextra -Werror -std=c++14 $(shell ../lib/SDL2/bin/sdl2-config --cflags) -fPIC
INCLUDES = -I ./src -I ../src
LIB = $(shell ../lib/SDL2/bin/sdl2-config --libs)

CC = clang++

all: $(NAME)

$(NAME): $(O_FILES)
	echo $^
	$(CC) -shared -fPIC $(FLAGS) $^ $(LIB) $(SRCI) -o $@ && echo "Done"

$(O_DIR)%.o: $(C_DIR)%.cpp
	@mkdir -p $(O_DIR)
	$(CC) $(FLAGS) $(INCLUDES) -o $@ -c $<

clean:
	@rm -Rf $(O_DIR)

fclean: clean
	@rm -f $(NAME) test_$(NAME)
	@rm -Rf .tmp/

re: fclean all

debug: FLAGS+=-g
debug: re

.PHONY: clean all fclean re
