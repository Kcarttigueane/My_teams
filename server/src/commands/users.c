/*
** EPITECH PROJECT, 2022
** MyTeams
** File description:
** users.c
*/

#include "../../include/server.h"

void users(__attribute_maybe_unused__ list_args_t* args)
{
    printf("USERS\r\n");
    dprintf(args->client->client_socket_fd, "200");
    print_users();
}
