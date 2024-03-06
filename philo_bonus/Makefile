    SHELL    = bash
    NAME     = philo_bonus
     CC      = clang
   CFLAGS    = -Wall -Wextra -Werror
   INCLUDE   = ./include
    SRCS     = main_bonus.c utils_bonus.c routine_bonus.c procs_sems_bonus.c
 SRCS_FOLDER = srcs
 OBJS_FOLDER = objs
    OBJS    := $(addprefix $(OBJS_FOLDER)/, $(SRCS:.c=.o))
    SRCS    := $(addprefix $(SRCS_FOLDER)/, $(SRCS))
   _CLEAR    = \x1b[2K\r
   _BOLD     = \x1b[1m
   _GREEN    = \x1b[32m
   _YELLOW   = \x1b[33m
   _CYAN     = \x1b[36m
   _END      = \x1b[0m
   _UP       = \x1b[1A

all: logo $(NAME)

$(NAME): $(OBJS_FOLDER) $(OBJS)
	@$(CC) $(CFLAGS) $(OBJS) -lc -lpthread -o $(NAME)
	@printf "$(_CLEAR)\t$(_BOLD)$(_GREEN)[$(_END)Compiled   $(_BOLD)$(_CYAN)$(NAME)$(_GREEN)]$(_END)\n\n"

$(OBJS_FOLDER):
	@mkdir -p $@
	@printf "\t$(_BOLD)$(_GREEN)[$(_END)Created $(_BOLD)$(_CYAN)objects folder$(_GREEN)]$(_END)\n"

$(OBJS_FOLDER)/%.o: $(SRCS_FOLDER)/%.c
	@printf "\t$(_CLEAR)$(_BOLD)$(_GREEN)[$(_END)Compiling $(_BOLD)$(_CYAN)$<$(_GREEN)]$(_END)"
	@$(CC) $(CFLAGS) -I$(INCLUDE) -c $< -o $@

clean:
	@rm -fr $(OBJS_FOLDER)
	@printf "\n\t$(_BOLD)$(_YELLOW)[$(_END)Removed $(_BOLD)$(_CYAN)objects folder$(_YELLOW)]$(_END)\n\n"

fclean: clean
	@rm -fr $(NAME)
	@printf "$(_UP)\t$(_BOLD)$(_YELLOW)[$(_END)Removed    $(_BOLD)$(_CYAN)$(NAME)$(_YELLOW)]$(_END)\n\n"

re: fclean all

logo:
	@printf "\n    $(_CYAN)┌─┐┬ ┬┬┬  ┌─┐┌─┐┌─┐┌─┐┬ ┬┌─┐┬─┐┌─┐  ┌┐ ┌─┐┌┐┌┬ ┬┌─┐\n"
	@printf "    ├─┘├─┤││  │ │└─┐│ │├─┘├─┤├┤ ├┬┘└─┐  ├┴┐│ │││││ │└─┐\n"
	@printf "    ┴  ┴ ┴┴┴─┘└─┘└─┘└─┘┴  ┴ ┴└─┘┴└─└─┘  └─┘└─┘┘└┘└─┘└─┘\n\n\n$(_END)"
.PHONY: all logo clean fclean re
