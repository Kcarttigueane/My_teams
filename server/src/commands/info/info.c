/*
** EPITECH PROJECT, 2022
** MyTeams
** File description:
** info.c
*/

#include "../../../include/server.h"

static void handle_info_user(list_args_t* args)
{
    user_t* user = find_user_by_uuid(args->db, args->client->current_user_uuid);

    if (!user)
        dprintf(args->client->socket_fd, UNKNOWN_USER_RESP, UNKNOWN_USER,
        args->client->current_user_uuid);
    else
        dprintf(args->client->socket_fd, INFO_USER_RESP, INFO_USER,
        user->username, user->uuid, user->is_logged_in ? "true" : "false");
}

static void handle_info_team(list_args_t* args)
{
    team_t* team = find_team_by_uuid(args->db, args->client->current_team_uuid);
    char *timestamp = timestamp_to_string(team->created_at);

    if (!team)
        dprintf(args->client->socket_fd, UNKNOWN_TEAM_RESP, UNKNOWN_TEAM,
        args->client->current_team_uuid);
    else
        dprintf(args->client->socket_fd, INFO_TEAM_RESP, INFO_TEAM, team->uuid,
        team->name, team->description, team->users_count, timestamp);

    free(timestamp);
}

static void handle_info_channel(list_args_t* args)
{
    team_t* team;
    channel_t* channel;

    if (!validate_team_channel(args, &team, &channel))
        return;

    char* timestamp = timestamp_to_string(team->created_at);

    if (!channel)
        dprintf(args->client->socket_fd, UNKNOWN_CHANNEL_RESP, UNKNOWN_CHANNEL,
        args->client->current_channel_uuid);
    else
        dprintf(args->client->socket_fd, INFO_CHANNEL_RESP, INFO_CHANNEL,
        channel->uuid, channel->name, channel->description,
        channel->team_uuid, timestamp);

    free(timestamp);
}

static void handle_info_thread(list_args_t* args)
{
    team_t* team = NULL;
    channel_t* channel = NULL;
    thread_t* thread = NULL;

    if (!validate_team_channel_thread(args, &team, &channel, &thread)) return;
    if (!is_thread_related_to_channel_to_team(team, channel, thread)) {
        dprintf(args->client->socket_fd, UNKNOWN_THREAD_RESP, UNKNOWN_THREAD,
        args->client->current_thread_uuid);
        return;
    }
    char* timestamp = timestamp_to_string(team->created_at);
    if (!thread)
        dprintf(args->client->socket_fd, UNKNOWN_THREAD_RESP, UNKNOWN_THREAD,
        args->client->current_thread_uuid);
    else
        dprintf(args->client->socket_fd, INFO_THREAD_RESP, INFO_THREAD,
        thread->uuid, thread->title, thread->message,
        thread->related_channel_uuid, thread->creator_uuid, timestamp);

    free(timestamp);
}

void info(list_args_t* args)
{
    switch (args->client->use_args_count) {
        case 0:
            handle_info_user(args);
            break;
        case 1:
            handle_info_team(args);
            break;
        case 2:
            handle_info_channel(args);
            break;
        case 3:
            handle_info_thread(args);
            break;
        default:
            send_error(args->client->socket_fd, INTERNAL_SERVER_ERROR,
            "Use /use command first");
            break;
    }
}
