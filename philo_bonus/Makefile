CFLAGS = -Wall -Werror -Wextra

NAME = philo_bonus

CC = cc -pthread

SRC = actions_bonus.c parsing_bonus.c philo_bonus.c philo_init.c
OBJS = actions_bonus.o parsing_bonus.o philo_bonus.o philo_init.o

INCLUDE = philo_bonus.h

all : $(NAME)

$(NAME) : $(OBJS) $(INCLUDE)
	$(CC) $(CFLAGS) $(OBJS)  -o $(NAME)

clean :
	rm -rf $(OBJS)

fclean : clean
	rm -rf $(NAME)

re : fclean all
