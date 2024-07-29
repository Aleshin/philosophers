CC = gcc -pthread -fsanitize=thread -g
CFLAGS = -Wall -Wextra -Werror
RM = rm -f

NAME = philo
HEADER = philo.h

SRCS =	philo.c init.c check_status.c monitor.c

OBJS = $(SRCS:.c=.o)

%.o:%.c 	$(HEADER) Makefile
			$(CC) $(CFLAGS) -c $< -o $@

all: 		$(NAME)

$(NAME): 	$(OBJS)
			$(CC) $(CFLAGS) $(OBJS) -o $(NAME)

clean:
			$(RM) $(OBJS)

fclean: 	clean
			$(RM) $(NAME)

re:			fclean all

.PHONY: all clean fclean re
