/*
** EPITECH PROJECT, 2022
** MyTeams
** File description:
** msgs.c
*/

#include "../../include/server.h"

void msgs(list_args_t* args)
{
    remove_quotes(args->split_command[1]);

    discussion_t* discussion = find_discussion_by_users(
        args->db, args->client->current_user_uuid, args->split_command[1]);

    if (discussion == NULL) {
        dprintf(args->client->socket_fd, UNKNOWN_USER_RESP, UNKNOWN_USER,
        args->split_command[1]);
        return;
    }

    char* json_resp = list_discussion_messages(discussion);
    send(args->client->socket_fd, json_resp, strlen(json_resp), 0);

    free(json_resp);
}
