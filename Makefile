CXX = g++

NAME = iniparser

SRC = main.cpp \
    parser_ini.cpp

OBJ = $(SRC:.cpp=.o)

WARNING_FLAGS = -Wall -Wextra
DEBUG_FLAGS = -g

CXXFLAGS = -std=c++17 $(WARNING_FLAGS) $(DEBUG_FLAGS)
LDFLAGS =

all : $(NAME)

$(NAME) : $(OBJ)
	$(CXX) -o $(NAME) $(OBJ) $(LDFLAGS)

clean :
	rm -f $(OBJ)

fclean : clean
	rm -f $(NAME)

re : fclean all