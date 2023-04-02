/*
** EPITECH PROJECT, 2022
** B-NWP-400-LYN-4-1-myteams-jules.dutel
** File description:
** use_helper_functions.c
*/

#include "../../include/server.h"

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
