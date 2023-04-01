/*
** EPITECH PROJECT, 2022
** MyTeams
** File description:
** main.c
*/

#include "include/server.h"

int main(int argc, char const* argv[])
{
    if (!are_arguments_valid(argc, argv)) return ERROR;
    if (setup_signal_handler() == ERROR) return ERROR;

    server_data_t server_data = {
        .PORT = atoi(argv[1]),
        .socket_fd = 0,
        .readfds = {{0}},
    };

    database_t db = init_database();

    if (initialize_server(&server_data) == ERROR)
        return handle_error("Server initialization failed");

    server_loop(&server_data, &db);

    save_database(&db);

    free_database(&db);
    return SUCCESS;
};
