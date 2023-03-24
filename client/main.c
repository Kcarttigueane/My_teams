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

    client_data_t client_data = {
        .ip = argv[1],
        .port = atoi(argv[2]),
        .socket_fd = 0,
        .read_fds = {{0}},
    };

    if (init_client(&client_data) == ERROR)
        return ERROR;

    if (client_loop(&client_data) == ERROR)
        return ERROR;

    return 0;
}
