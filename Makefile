
NAME = philo

SRCS = philo.c parsing.c utils.c\

CC = cc

CFLAGS = -Wall -Werror -Wextra 

OBJS = $(SRCS:.c=.o)

all : $(NAME)

$(NAME) : $(OBJS)
		$(CC) $(CFLAGS) $(OBJS) -o $(NAME)
clean :
	rm -rf $(OBJS)

fclean : clean
	rm -rf $(NAME)

re : fclean all