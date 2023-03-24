/*
** EPITECH PROJECT, 2022
** MyTeams
** File description:
** logout.c
*/

#include "../../include/server.h"

void logout(list_args_t* args)
{
    printf("LOGOUT\n");
    if (!args->client->is_logged) {
        dprintf(args->client->client_socket_fd, "530 Not logged in");
        return;
    }
    args->client->current_user_uuid[0] = '\0';
    args->client->is_logged = false;
    dprintf(args->client->client_socket_fd, "200");
    printf("User %s logged out\n", args->client->current_user_uuid);
}
