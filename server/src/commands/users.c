/*
** EPITECH PROJECT, 2022
** MyTeams
** File description:
** users.c
*/

#include "../../include/server.h"

void users(list_args_t* args)
{
    printf("USERS\r\n");
    dprintf(args->client->client_socket_fd, "200");
    print_users(args->db);
}
