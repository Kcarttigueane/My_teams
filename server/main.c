/*
** EPITECH PROJECT, 2022
** MyTeams
** File description:
** main.c
*/

#include "include/server.h"

int main(int argc, char const* argv[])
{
    if (!are_arguments_valid(argc, argv))
        return ERROR;

    signal(SIGINT, sigint_handler);
    signal(SIGTERM, sigterm_handler);

    server_data_t server_data = {
        .PORT = atoi(argv[1]),
        .socket_fd = 0,
        .readfds = {{0}},
    };
    database_t = init_database();

    if (initialize_server(&server_data) == ERROR)
        return handle_error("Server initialization failed");

    server_loop(&server_data);

    return SUCCESS;
};
