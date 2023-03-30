/*
** EPITECH PROJECT, 2022
** MyTeams
** File description:
** info.c
*/

#include "../../../include/server.h"

void handle_info_user(list_args_t* args)
{
    user_t* user = find_user_by_uuid(args->db, args->client->current_user_uuid);

    if (!user)
        send_error(args->client->socket_fd, INTERNAL_SERVER_ERROR,
        "User not found");
    else
        dprintf(args->client->socket_fd, INFO_USER_RESP, INFO_USER,
        user->username, user->uuid);
}

void handle_info_team(list_args_t* args)
{
    team_t* team = find_team_by_uuid(args->db, args->client->current_team_uuid);

    if (!team)
        send_error(args->client->socket_fd, INTERNAL_SERVER_ERROR,
        "Team not found");
    else
        dprintf(args->client->socket_fd, INFO_TEAM_RESP, INFO_CHANNEL,
        team->uuid, team->name, team->description, team->users_count,
        ctime(&team->created_at));
}

static void handle_info_channel(list_args_t* args)
{
    channel_t* channel =
        find_channel_by_uuid(args->db, args->client->current_channel_uuid);

    if (!channel)
        send_error(args->client->socket_fd, INTERNAL_SERVER_ERROR,
        "Channel not found");
    else
        dprintf(args->client->socket_fd, INFO_CHANNEL_RESP, INFO_CHANNEL,
        channel->uuid, channel->name, channel->description, channel->team_uuid,
        channel->nb_users, ctime(&channel->created_at));
}

static void handle_info_thread(list_args_t* args)
{
    thread_t* thread =
        find_thread_by_uuid(args->db, args->client->current_thread_uuid);

    if (!thread)
        send_error(args->client->socket_fd, INTERNAL_SERVER_ERROR,
        "Thread not found");
    else
        dprintf(args->client->socket_fd, INFO_THREAD_RESP, INFO_THREAD_RESP,
        thread->uuid, thread->title, thread->message,
        thread->related_channel_uuid,
        thread->creator_uuid, ctime(&thread->created_at));
}

void info(__attribute_maybe_unused__ list_args_t* args)
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
}
