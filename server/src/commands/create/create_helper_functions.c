/*
** EPITECH PROJECT, 2022
** B-NWP-400-LYN-4-1-myteams-jules.dutel
** File description:
** create_helper_functions.c
*/

#include "../../../include/server.h"

void team_creation_send_json_resp(list_args_t* args, team_t* new_team)
{
    server_event_team_created(new_team->uuid, new_team->name,
    args->client->current_user_uuid);

    dprintf(args->client->socket_fd, CREATE_TEAM_RESP,
    TEAM_CREATED_NOTIFICATION, new_team->uuid, new_team->name,
    new_team->description);

    for (size_t i = 0; i < MAX_CLIENTS; i++) {
        if (args->clients[i].socket_fd == 0)
            continue;
        if (args->clients[i].is_logged)
            dprintf(args->clients[i].socket_fd, CREATE_TEAM_RESP,
            TEAM_CREATED, new_team->uuid, new_team->name,
            new_team->description);
    }
}

void team_channel_send_json_resp(list_args_t* args, channel_t* new_channel,
team_t* team)
{
    server_event_channel_created(new_channel->team_uuid, new_channel->uuid,
    new_channel->name);

    dprintf(args->client->socket_fd, CREATE_CHANNEL_RESP,
    CHANNEL_CREATED_NOTIFICATION, new_channel->uuid, new_channel->name,
    new_channel->description);

    for (size_t i = 0; i < MAX_CLIENTS; i++) {
        if (args->clients[i].socket_fd == 0)
            continue;
        for (size_t j = 0; j < 10; j++) {
            (args->clients[i].is_logged &&
            !strcmp(args->clients[i].current_user_uuid, team->users[j])) ?
                dprintf(args->clients[i].socket_fd, CREATE_CHANNEL_RESP,
                CHANNEL_CREATED, new_channel->uuid,
                new_channel->name, new_channel->description) :
                (void)0;
        }
    }
}

void thread_creation_send_json_resp(list_args_t* args, thread_t* new_thread)
{
    char* timestamp = timestamp_to_string(new_thread->created_at);

    dprintf(args->client->socket_fd, CREATE_THREAD_RESP,
    THREAD_CREATED_NOTIFICATION,
    new_thread->uuid, new_thread->title, new_thread->message,
    new_thread->related_channel_uuid, new_thread->creator_uuid,
    timestamp);

    server_event_thread_created(new_thread->related_channel_uuid,
    new_thread->uuid,
    args->client->current_user_uuid,
    new_thread->title, new_thread->message);

    dprintf(args->client->socket_fd, CREATE_THREAD_RESP,
    THREAD_CREATED, new_thread->uuid, new_thread->title, new_thread->message,
    new_thread->related_channel_uuid, new_thread->creator_uuid,
    timestamp);
    free(timestamp);
}

void reply_creation_send_json_resp(list_args_t* args, reply_t* new_reply,
char *thread_uuid, char *team_uuid)
{
    char *timestamp = timestamp_to_string(new_reply->created_at);
    dprintf(args->client->socket_fd, CREATED_REPLY_RESP, THREAD_REPLY_CREATED,
    team_uuid, new_reply->body, new_reply->creator_uuid, thread_uuid,
    timestamp);

    server_event_reply_created(thread_uuid, args->client->current_user_uuid,
    new_reply->body);

    dprintf(args->client->socket_fd, CREATED_REPLY_RESP,
    REPLY_CREATED_NOTIFICATION, team_uuid, new_reply->body,
    new_reply->creator_uuid,  thread_uuid, timestamp);
    free(timestamp);
}

bool error_handling_name_and_description(int control_socket, char *name,
char *description)
{
    if (strlen(name) > MAX_NAME_LENGTH) {
        send_error(control_socket, INTERNAL_SERVER_ERROR, "Name too long");
        return false;
    }

    if (strlen(description) > MAX_DESCRIPTION_LENGTH) {
        send_error(control_socket, INTERNAL_SERVER_ERROR,
        "Description too long");
        return false;
    }

    return true;
}
