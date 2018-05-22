NAME = nibbler

C_DIR =	src
C_FILES = src/main.cpp src/Level.cpp src/Snake.cpp

O_DIR =	.tmp/obj
O_FILES = $(C_FILES:$(C_DIR)%.cpp=$(O_DIR)%.o)

FLAGS = -Wall -Wextra -Werror -std=c++14
INCLUDES = -I ./src
LIB = -ldl

CC = clang++

all: $(NAME)

$(NAME): $(O_FILES)
	make -C ./sdl
	make -C ./ncurses
	make -C ./imgui
	$(CC) $(FLAGS) $^ $(LIB) $(SRCI) -o $@ && echo "Done"

$(O_DIR)%.o: $(C_DIR)%.cpp
	@mkdir -p $(O_DIR)
	$(CC) $(FLAGS) $(INCLUDES) -o $@ -c $<

clean:
	make clean -C ./sdl
	make clean -C ./ncurses
	make clean -C ./imgui
	@rm -Rf $(O_DIR)

fclean: clean
	make fclean -C ./sdl
	make fclean -C ./ncurses
	make fclean -C ./imgui
	@rm -f $(NAME) test_$(NAME)
	@rm -Rf .tmp/

re: fclean all

debug: FLAGS+=-g
debug: re

.PHONY: clean all fclean re
