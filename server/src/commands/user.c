/*
** EPITECH PROJECT, 2022
** MyTeams
** File description:
** user.c
*/

#include "../../include/server.h"

void user(list_args_t* args)
{
    remove_quotes(args->split_command[1]);

    user_t* user = find_user_by_uuid(args->db, args->split_command[1]);

    if (user == NULL) {
        send_error(args->client->socket_fd, 530,
        "User not found");
        return;
    }

    dprintf(args->client->socket_fd, USER_DETAILS, INFO_USER, user->username,
    user->uuid);
}
