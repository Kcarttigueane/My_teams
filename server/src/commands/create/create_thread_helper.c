/*
** EPITECH PROJECT, 2022
** B-NWP-400-LYN-4-1-myteams-jules.dutel
** File description:
** create_thread_helper.c
*/

#include "../../../include/server.h"

static void notify_team_members(list_args_t* args, thread_t* new_thread,
team_t* team, char *timestamp)
{
    for (size_t i = 0; i < MAX_CLIENTS; i++) {
        if (args->clients[i].socket_fd == 0)
            continue;
        for (size_t j = 0; j < 10; j++) {
            (args->clients[i].is_logged &&
                !strcmp(args->clients[i].current_user_uuid, team->users[j]))
                ? dprintf(args->clients[i].socket_fd, CREATE_THREAD_RESP,
                    THREAD_CREATED, new_thread->uuid, new_thread->title,
                    new_thread->message, new_thread->related_channel_uuid,
                    new_thread->creator_uuid, timestamp)
                : (void)0;
        }
    }

}

void thread_creation_send_json_resp(list_args_t* args, thread_t* new_thread,
team_t* team)
{
    char* timestamp = timestamp_to_string(new_thread->created_at);

    dprintf(args->client->socket_fd, CREATE_THREAD_RESP,
    THREAD_CREATED_NOTIFICATION, new_thread->uuid, new_thread->title,
    new_thread->message, new_thread->related_channel_uuid,
    new_thread->creator_uuid, timestamp);

    server_event_thread_created(new_thread->related_channel_uuid,
    new_thread->uuid,
    args->client->current_user_uuid,
    new_thread->title, new_thread->message);

    notify_team_members(args, new_thread, team, timestamp);

    free(timestamp);
}
