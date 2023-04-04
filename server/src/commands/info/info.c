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

    if (!team)
        dprintf(args->client->socket_fd, UNKNOWN_TEAM_RESP, UNKNOWN_TEAM,
        args->client->current_team_uuid);
    else
        dprintf(args->client->socket_fd, INFO_TEAM_RESP, INFO_TEAM, team->uuid,
        team->name, team->description, team->users_count,
        ctime(&team->created_at));
}

static void handle_info_channel(list_args_t* args)
{
    team_t* team;
    channel_t* channel;

    if (!validate_team_channel(args, &team, &channel))
        return;

    if (!channel)
        dprintf(args->client->socket_fd, UNKNOWN_CHANNEL_RESP, UNKNOWN_CHANNEL,
        args->client->current_channel_uuid);
    else
        dprintf(args->client->socket_fd, INFO_CHANNEL_RESP, INFO_CHANNEL,
        channel->uuid, channel->name, channel->description,
        channel->team_uuid, channel->nb_users,
        ctime(&channel->created_at));
}

static void handle_info_thread(list_args_t* args)
{
    team_t* team;
    channel_t* channel;
    thread_t* thread;

    if (!validate_team_channel_thread(args, &team, &channel, &thread))
        return;
    if (!is_thread_related_to_channel_to_team(team, channel, thread)) {
        dprintf(args->client->socket_fd, UNKNOWN_THREAD_RESP, UNKNOWN_THREAD,
        args->client->current_thread_uuid);
        return;
    }

    if (!thread)
        dprintf(args->client->socket_fd, UNKNOWN_THREAD_RESP, UNKNOWN_THREAD,
        args->client->current_thread_uuid);
    else
        dprintf(args->client->socket_fd, INFO_THREAD_RESP, INFO_THREAD_RESP,
        thread->uuid, thread->title, thread->message,
        thread->related_channel_uuid, thread->creator_uuid,
        ctime(&thread->created_at));
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
            break;
    }
    args->client->use_args_count = FAILURE;
}
