CFLAGS = -Wall -Werror -Wextra

NAME = philo

CC = cc -pthread 

SRC = parsing.c philo.c ft_actions.c utils.c
OBJS = parsing.o philo.o ft_actions.o utils.o

INCLUDE = philo.h

all : $(NAME)

$(NAME) : $(OBJS) $(INCLUDE)
	$(CC) $(CFLAGS) $(OBJS)  -o $(NAME)

clean :
	rm -rf $(OBJS)

fclean : clean
	rm -rf $(NAME)

re : fclean all
