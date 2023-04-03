/*
** EPITECH PROJECT, 2022
** MyTeams
** File description:
** msgs.c
*/

#include "../../include/server.h"

void msgs(list_args_t* args)
{
    char *uuid = args->split_command[1];

    user_t* user = find_user_by_uuid(args->db, uuid);
    if (!user) {
        dprintf(args->client->socket_fd, UNKNOWN_USER_RESP, UNKNOWN_USER, uuid);
        return;
    }

    discussion_t* discussion = find_discussion_by_users(
        args->db, args->client->current_user_uuid, uuid);

    if (!discussion) {
        dprintf(args->client->socket_fd, NO_MESSAGES_RESP,
        PRINT_PRIVATE_MESSAGES, uuid);
        return;
    }
    char* json_resp = list_discussion_messages(discussion);
    send(args->client->socket_fd, json_resp, strlen(json_resp), 0);

    free(json_resp);
}
