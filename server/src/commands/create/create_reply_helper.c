/*
** EPITECH PROJECT, 2022
** B-NWP-400-LYN-4-1-myteams-jules.dutel
** File description:
** create_reply_helper.c
*/

#include "../../../include/server.h"

void reply_creation_send_json_resp(list_args_t* args, reply_t* new_reply,
char *thread_uuid, team_t *team)
{
    char *timestamp = timestamp_to_string(new_reply->created_at);
    dprintf(args->client->socket_fd, CREATED_REPLY_RESP,
    REPLY_CREATED_NOTIFICATION, team->uuid, new_reply->body,
    new_reply->creator_uuid, thread_uuid, timestamp);

    server_event_reply_created(thread_uuid, args->client->current_user_uuid,
    new_reply->body);
    for (size_t i = 0; i < MAX_CLIENTS; i++) {
        if (args->clients[i].socket_fd == 0)
            continue;
        for (size_t j = 0; j < 10; j++) {
            (args->clients[i].is_logged &&
                !strcmp(args->clients[i].current_user_uuid, team->users[j]))
                ? dprintf(args->client->socket_fd, CREATED_REPLY_RESP,
                THREAD_REPLY_CREATED, team->uuid, new_reply->body,
                new_reply->creator_uuid, thread_uuid, timestamp)
                : (void)0;
        }
    }
    free(timestamp);
}
