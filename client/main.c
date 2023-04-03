/*
** EPITECH PROJECT, 2022
** MyTeams
** File description:
** main.c
*/

#include "include/client.h"

int main(int argc, char* argv[])
{
    if (!are_arguments_valid(argc, argv))
        return ERROR;

    if (setup_signal_handler() == ERROR)
        return ERROR;

    client_data_t client_data = {
        .socket_fd = connect_to_server(argv[1], atoi(argv[2])),
        .read_fds = {{0}},
    };

    if (client_data.socket_fd == FAILURE)
        return ERROR;

    return client_loop(&client_data);
}
