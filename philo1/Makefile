SHELL = bash

NAME = philo

CC = clang

CFLAGS = -Wall -Wextra -Werror -fsanitize=thread -g

INCLUDE = ./include

SRCS = main.c utils.c routine.c threads_mutexes.c

SRCS_FOLDER = srcs/

OBJS = $(addprefix $(SRCS_FOLDER),$(SRCS:.c=.o))

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
