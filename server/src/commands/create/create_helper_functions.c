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

    dprintf(args->client->socket_fd, CREATE_TEAM_RESP, TEAM_CREATED,
    new_team->uuid, new_team->name, new_team->description);

    dprintf(args->client->socket_fd, CREATE_TEAM_RESP,
    TEAM_CREATED_NOTIFICATION, new_team->uuid, new_team->name,
    new_team->description);
}

void team_channel_send_json_resp(list_args_t* args, channel_t* new_channel)
{
    server_event_channel_created(new_channel->team_uuid, new_channel->uuid,
    new_channel->name);

    dprintf(args->client->socket_fd, CREATE_CHANNEL_RESP, CHANNEL_CREATED,
    new_channel->uuid, new_channel->name, new_channel->description);

    dprintf(args->client->socket_fd, CREATE_CHANNEL_RESP,
    CHANNEL_CREATED_NOTIFICATION, new_channel->team_uuid, new_channel->uuid,
    new_channel->name, new_channel->description);
}

void thread_creation_send_json_resp(list_args_t* args, thread_t* new_thread)
{
    dprintf(args->client->socket_fd, CREATE_THREAD_RESP, THREAD_CREATED,
    new_thread->uuid, new_thread->title, new_thread->message,
    new_thread->related_channel_uuid, new_thread->creator_uuid,
    (long)new_thread->created_at);

    server_event_thread_created(new_thread->related_channel_uuid,
    new_thread->uuid,
    args->client->current_user_uuid,
    new_thread->title, new_thread->message);

    dprintf(args->client->socket_fd, CREATE_THREAD_RESP,
    THREAD_CREATED_NOTIFICATION,
    new_thread->uuid, new_thread->title, new_thread->message,
    new_thread->related_channel_uuid, new_thread->creator_uuid,
    (long)new_thread->created_at);
}

bool validate_team_channel_thread(list_args_t* args, team_t** team,
channel_t** channel, thread_t** thread)
{
    *team = find_team_by_uuid(args->db, args->client->current_team_uuid);
    if (*team == NULL) {
        dprintf(args->client->socket_fd, UNKNOWN_TEAM_RESP, UNKNOWN_TEAM,
        args->client->current_team_uuid);
        return false;
    }
    *channel =
        find_channel_by_uuid(args->db, args->client->current_channel_uuid);
    if (*channel == NULL) {
        dprintf(args->client->socket_fd, UNKNOWN_CHANNEL_RESP, UNKNOWN_CHANNEL,
        args->client->current_channel_uuid);
        return false;
    }
    *thread = find_thread_by_uuid(args->db, args->client->current_thread_uuid);
    if (*thread == NULL) {
        dprintf(args->client->socket_fd, UNKNOWN_THREAD_RESP, UNKNOWN_THREAD,
        args->client->current_thread_uuid);
        return false;
    }
    return true;
}

bool validate_team_channel(list_args_t* args, team_t** team,
channel_t** channel)
{
    *team = find_team_by_uuid(args->db, args->client->current_team_uuid);
    if (*team == NULL) {
        dprintf(args->client->socket_fd, UNKNOWN_TEAM_RESP, UNKNOWN_TEAM,
        args->client->current_team_uuid);
        return false;
    }
    *channel =
        find_channel_by_uuid(args->db, args->client->current_channel_uuid);
    if (*channel == NULL) {
        dprintf(args->client->socket_fd, UNKNOWN_CHANNEL_RESP, UNKNOWN_CHANNEL,
        args->client->current_channel_uuid);
        return false;
    }
    if (!is_channel_related_to_team(*team, *channel)) {
        dprintf(args->client->socket_fd, UNKNOWN_CHANNEL_RESP, UNKNOWN_CHANNEL,
        args->client->current_channel_uuid);
        return false;
    }
    return true;
}
