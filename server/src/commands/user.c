/*
** EPITECH PROJECT, 2022
** MyTeams
** File description:
** user.c
*/

#include "../../include/server.h"

void user(list_args_t* args)
{
    char *uuid = args->split_command[1];

    if (strlen(uuid) != (MAX_UUID_LENGTH - 1)) {
        send_error(args->client->socket_fd, UNKNOWN_USER, "Invalid UUID");
        return;
    }

    user_t* user = find_user_by_uuid(args->db, uuid);

    if (!user) {
        dprintf(args->client->socket_fd, UNKNOWN_USER_RESP, UNKNOWN_USER, uuid);
        return;
    }

    dprintf(args->client->socket_fd, USER_DETAILS_RESP, INFO_USER,
    user->username, user->uuid, user->is_logged_in ? "true" : "false");
}
