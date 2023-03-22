##
## EPITECH PROJECT, 2023
## MyTeams
## File description:
## Makefile
##

CC ?=gcc
RM = rm -f

NAME = ../myteams_server

SRCS = $(shell find ../lib -type f -name "*.c") \
       $(shell find . -type f -name "*.c") \

OBJS = $(SRCS:.c=.o)
DEPS = $(OBJS:.o=.d)

CFLAGS += -Wall -Wextra -I ../include -g3 -luuid

# Add color to output
COLOR_RESET   = \033[0m
COLOR_PENDING = \033[01;33m
COLOR_SUCCESS = \033[01;32m
COLOR_DEFAULT = \033[01;36m
GREEN	=	\033[0;32m


all: $(NAME)

$(NAME): $(OBJS)
	@printf "\033[0;36mserver \033[0;33m▷  $(COLOR_PENDING)Linking...\
	$(COLOR_RESET)\n"
	@$(CC) $(CFLAGS) -o $(NAME) $(OBJS)
	@printf "\033[0;36mserver \033[0;34m▷  $(COLOR_SUCCESS)Done.\
	$(COLOR_RESET)\n"

-include $(DEPS)

%.o: %.c
	@printf "\033[0;36mserver \033[0;34m▷  $(GREEN)「✔」	$(COLOR_DEFAULT)\
	Compiling $<...$(COLOR_RESET)\n"
	@$(CC) $(CFLAGS) -MMD -c $< -o $@

clean:
	@printf "\033[0;36mserve	r \033[0;33m▷  $(COLOR_PENDING)Cleaning...\
	$(COLOR_RESET)\n"
	@$(RM) $(OBJS)
	@$(RM) $(DEPS)
	@make -C ../tests fclean
	@printf "\033[0;36mserver \033[0;32m▷  $(COLOR_SUCCESS)Done.\
	$(COLOR_RESET)\n"

fclean: clean
	@printf "\033[0;36mserver \033[0;33m▷  $(COLOR_PENDING)\
	Full cleaning...$(COLOR_RESET)\n"
	@$(RM) $(NAME)
	@$(RM) $(wildcard vgcore*)
	@printf "\033[0;36mserver \033[0;32m▷  $(COLOR_SUCCESS)Done.\
	$(COLOR_RESET)\n"

re: fclean all

tests_run:
	make -C ../tests all


.PHONY: all clean fclean re tests_run
