
NAME = philo

SRCS = philo.c parsing.c utils.c actions.c end_simulation.c free_all.c

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