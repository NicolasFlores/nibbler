NAME = nibbler_imgui.so

C_DIR =	src
C_FILES = src/ImGuiGraphicLib.cpp src/Shader.cpp src/Camera.cpp

O_DIR =	.tmp/obj
O_FILES = $(C_FILES:$(C_DIR)%.cpp=$(O_DIR)%.o)

FLAGS = -Wall -Wextra -Werror -std=c++14 $(shell ../lib/SDL2/bin/sdl2-config --cflags) -fPIC
INCLUDES = -I ./src -I ../src -I ../lib/imgui/include -I ../lib/glm
ifeq ($(shell uname),Darwin)
	LIB = $(shell ../lib/SDL2/bin/sdl2-config --libs) -framework OpenGl -framework CoreFoundation
else
	LIB = $(shell ../lib/SDL2/bin/sdl2-config --libs) -ldl -lGL
endif

CC = clang++

all: $(NAME)

$(NAME): $(O_FILES)
	echo $^
	$(CC) --shared $(FLAGS) $^ ../lib/imgui/bin/imgui.a $(LIB) $(SRCI) -o $@ && echo "Done"

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
