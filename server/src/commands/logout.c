/*
** EPITECH PROJECT, 2022
** MyTeams
** File description:
** logout.c
*/

#include "../../include/server.h"

void logout(list_args_t* args)
{
    user_t* user = find_user_by_uuid(args->db, args->client->current_user_uuid);

    if (user == NULL)
        send_error(args->client->socket_fd, UNKNOWN_USER, "Unknown user");


    args->client->current_user_uuid[0] = '\0';
    args->client->is_logged = false;

    dprintf(args->client->socket_fd, LOGOUT_JSON_RESP,
    DISCONNECTION_SUCCESSFUL, user->username, user->uuid);

    printf("User %s logged out\n", args->client->current_user_uuid);
}
