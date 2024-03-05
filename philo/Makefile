    SHELL    = bash
    NAME     = philo
     CC      = clang
   CFLAGS    = -Wall -Wextra -Werror
   INCLUDE   = ./include
    SRCS     = main.c utils.c routine.c threads_mutexes.c
 SRCS_FOLDER = srcs
 OBJS_FOLDER = objs
    OBJS    := $(addprefix $(OBJS_FOLDER)/, $(SRCS:.c=.o))
    SRCS    := $(addprefix $(SRCS_FOLDER)/, $(SRCS))
   _CLEAR    = \x1b[2K\r
   _BOLD     = \x1b[1m
   _GREEN    = \x1b[32m
   _YELLOW   = \x1b[33m

all: $(NAME)

$(NAME): $(OBJS_FOLDER) $(OBJS)
	@$(CC) $(CFLAGS) $(OBJS) -lc -lpthread -o $(NAME)
	@printf "$(_CLEAR)$(_BOLD)$(_GREEN)[Compiled         $(NAME)]\n"

$(OBJS_FOLDER):
	@mkdir -p $@
	@printf "$(_BOLD)$(_GREEN)[Created objects folder]\n"

$(OBJS_FOLDER)/%.o: $(SRCS_FOLDER)/%.c
	@printf "$(_CLEAR)$(_BOLD)$(_GREEN)[Compiling $<]"
	@$(CC) $(CFLAGS) -I$(INCLUDE) -c $< -o $@

clean:
	@rm -fr $(OBJS_FOLDER)
	@printf "$(_BOLD)$(_YELLOW)[Removed objects folder]\n"

fclean: clean
	@rm -fr $(NAME)
	@printf "$(_BOLD)$(_YELLOW)[Removed          $(NAME)]\n"

re: fclean all

.PHONY: all clean fclean re
