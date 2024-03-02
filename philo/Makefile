SHELL = bash

NAME = philo

CC = clang

CFLAGS = -Wall -Wextra -Werror -fsanitize=thread -g

INCLUDE = ./include

SRCS = srcs/main.c    \
	   srcs/init.c    \
	   srcs/check.c   \
	   srcs/utils.c   \
	   srcs/destroy.c \
	   srcs/actions.c \
	   srcs/routine.c \
	   srcs/parsing.c \

OBJS = $(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -lc -lpthread -o $(NAME)

%.o: %.c
	$(CC) $(CFLAGS) -I$(INCLUDE) -c $< -o $@

clean:
	rm -fr $(OBJS)

fclean: clean
	rm -fr $(NAME)

re: fclean all

.PHONY: all clean fclean re
