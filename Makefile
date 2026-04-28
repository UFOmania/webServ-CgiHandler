FLAGS = -Wall -Wextra -Werror -std=c++98 -MMD -fsanitize=address
NAME= cgi

SRC = 	main.cpp\
		CgiHandler.cpp

OBJ = $(SRC:.cpp=.o)

DEPS = $(SRC:.cpp=.d)

all: $(NAME)

$(NAME): $(OBJ)
	c++ $(FLAGS) $(OBJ) -o $@

%.o:	%.cpp
	c++ $(FLAGS) -c $< -o $@

clean:
	rm -f $(OBJ) $(DEPS)

fclean:	clean
	rm -f $(NAME)

re: fclean all


-include $(deps)