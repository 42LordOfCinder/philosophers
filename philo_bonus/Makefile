SHELL = bash

NAME = philo_bonus

CC = clang

CFLAGS = -Wall -Wextra -Werror

INCLUDE = ./include

SRCS = main.c

SRCS_FOLDER = srcs

OBJS_FOLDER = objs

OBJS := $(addprefix $(OBJS_FOLDER)/, $(SRCS:.c=.o))

SRCS := $(addprefix $(SRCS_FOLDER)/, $(SRCS))

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME)

$(OBJS_FOLDER)/%.o: $(SRCS_FOLDER)/%.c
	mkdir -p $(@D)
	$(CC) $(CFLAGS) -I$(INCLUDE) -c $< -o $@

clean:
	rm -fr $(OBJS_FOLDER)

fclean: clean
	rm -fr $(NAME)

re: fclean all

.PHONY: all clean fclean re
