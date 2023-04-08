
NAME = philo

SRCS = philo.c parsing.c \

CC = cc

CFLAGS = -Wall -Werror -Wextra 

OBJ = $(SRCS:.c=.o)

all : $(NAME)

$(NAME) : $(OBJ)
		$(CC) $(CFLAGS) $(OBJ) -o $(NAME)

clean :
	rm -rf $(OBJS)

fclean : clean
	rm -rf $(NAME) $(OBJ)

re : fclean all
