NAME = nibbler_irrklang.so

SRC = IrrKlangSoundLib.cpp

OBJ = $(SRC:.cpp=.o)

FLAGS = -Wall -Wextra -Werror -std=c++14 -fPIC

LIBFLAGS = -shared -fPIC

DYLIB = ../lib/irrKlang/irrKlang-64bit-1.6.0/bin/macosx-gcc/libirrklang.dylib 

CC = clang++

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(FLAGS) $(LIBFLAGS) -o $(NAME) $(OBJ) $(DYLIB)
	# install_name_tool -change "/usr/local/lib/libirrklang.dylib" $(DYLIB) $(NAME)

%.o: %.cpp
	$(CC) $(FLAGS) -o $@ -c $<

clean:
	@rm -rf $(OBJ)

fclean: clean
	@rm -rf $(NAME)

re: fclean all
