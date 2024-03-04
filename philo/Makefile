SHELL = bash

NAME = philo

CC = clang

CFLAGS = -Wall -Wextra -Werror -fsanitize=thread

INCLUDE = ./include

SRCS = main.c utils.c routine.c threads_mutexes.c

SRCS_FOLDER = srcs

OBJS_FOLDER = objs

OBJS := $(addprefix $(OBJS_FOLDER)/, $(SRCS:.c=.o))

SRCS := $(addprefix $(SRCS_FOLDER)/, $(SRCS))

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -lc -lpthread -o $(NAME)

$(OBJS_FOLDER)/%.o: $(SRCS_FOLDER)/%.c
	mkdir -p $(@D)
	$(CC) $(CFLAGS) -I$(INCLUDE) -c $< -o $@

clean:
	rm -fr $(OBJS_FOLDER)

fclean: clean
	rm -fr $(NAME)

re: fclean all

.PHONY: all clean fclean re
