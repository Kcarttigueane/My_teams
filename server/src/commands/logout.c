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
        send_error(args->client->socket_fd, 530, "Not logged in");
        return;
    }

    args->client->current_user_uuid[0] = '\0';
    args->client->is_logged = false;

    send(args->client->socket_fd, LOGOUT_JSON_REP, strlen(LOGOUT_JSON_REP), 0);

    printf("User %s logged out\n", args->client->current_user_uuid);
}
