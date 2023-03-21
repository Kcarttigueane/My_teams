##
## EPITECH PROJECT, 2023
## MyTeams
## File description:
## Makefile
##

SERVER	=	server/
CLIENT	=	client/

COLOR_RESET   = \033[0m
COLOR_TITLE   = \033[01;31m

all: server client

server:
	@printf "$(COLOR_TITLE)[COMPILING SERVER...]$(COLOR_RESET)\n"
	@make -C $(SERVER) -s

client:
	@printf "$(COLOR_TITLE)[COMPILING CLIENT...]$(COLOR_RESET)\n"
	@make -C $(CLIENT) -s

clean:
	@printf "$(COLOR_TITLE)[CLEANING SERVER...]$(COLOR_RESET)\n"
	@make clean -C $(SERVER) -s
	@printf "$(COLOR_TITLE)[CLEANING CLIENT...]$(COLOR_RESET)\n"
	@make clean -C $(CLIENT) -s

fclean:
	@printf "$(COLOR_TITLE)[FCLEAN SERVER...]$(COLOR_RESET)\n"
	@make fclean -C $(SERVER) -s
	@printf "$(COLOR_TITLE)[FCLEAN CLIENT...]$(COLOR_RESET)\n"
	@make fclean -C $(CLIENT) -s

re:
	@printf "$(COLOR_TITLE)[RE SERVER...]$(COLOR_RESET)\n"
	@make re -C $(SERVER) -s
	@printf "$(COLOR_TITLE)[RE CLIENT...]$(COLOR_RESET)\n"
	@make re -C $(CLIENT) -s

.PHONY: all server client clean fclean re
