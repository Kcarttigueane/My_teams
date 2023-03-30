/*
** EPITECH PROJECT, 2022
** MyTeams
** File description:
** logout.c
*/

#include "../../include/server.h"

void logout(list_args_t* args)
{
    if (args->client->is_logged == false) {
        send_error(args->client->socket_fd, INTERNAL_SERVER_ERROR,
        "Not logged in");
        return;
    }

    args->client->current_user_uuid[0] = '\0';
    args->client->is_logged = false;

    dprintf(args->client->socket_fd, LOGOUT_JSON_RESP,
    DISCONNECTION_SUCCESSFUL);

    printf("User %s logged out\n", args->client->current_user_uuid);
}
