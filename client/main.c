/*
** EPITECH PROJECT, 2022
** MyTeams
** File description:
** main.c
*/

#include "include/client.h"

const char *command_list[] = {
    "/help",
    "/login",
    "/logout",
    "/users",
    "/user",
    "/send",
    "/messages",
    "/subscribe",
    "/subscribed",
    "/unsubscribe",
    "/use",
    "/create",
    "/list",
    "/info",
    NULL
};

int main(int argc, char *argv[])
{
    if (argc != 2)
        return ERROR;

    client_data_t client_data = {
        .ip = argv[1],
        .port = atoi(argv[2]),
        .socket_fd = 0,
        .read_fds = {{0}},
    };

    init_socket(&client_data);
    init_addresses(&client_data);
    connection(&client_data);

    client_loop(&client_data);

    return 0;
}
