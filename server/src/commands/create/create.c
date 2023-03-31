/*
** EPITECH PROJECT, 2022
** MyTeams
** File description:
** create.c
*/

#include "../../../include/server.h"

static void handle_create_team(list_args_t* args)
{
    team_t* new_teams =
        create_team(args->db, args->split_command[1], args->split_command[2]);

    if (new_teams == NULL)
        send_error(args->client->socket_fd, INTERNAL_SERVER_ERROR,
        "Team not created");

    dprintf(args->client->socket_fd, CREATE_TEAM_RESP, TEAM_CREATED,
    new_teams->uuid, new_teams->name, new_teams->description);
}

static void handle_create_channel(list_args_t* args)
{
    team_t* team = find_team_by_uuid(args->db, args->client->current_team_uuid);

    if (!team) {
        dprintf(args->client->socket_fd, UNKNOWN_TEAM_RESP, UNKNOWN_TEAM,
        args->client->current_team_uuid);
        send_error(args->client->socket_fd, UNKNOWN_TEAM, "Unknown team");
        return;
    }

    create_channel_params_t params = init_create_channel_params(args);

    channel_t* new_channel = create_channel(args->db, &params);

    if (!new_channel)
        send_error(args->client->socket_fd, INTERNAL_SERVER_ERROR,
        "Channel not created");

    dprintf(args->client->socket_fd, CREATE_CHANNEL_RESP, CHANNEL_CREATED,
    new_channel->uuid, new_channel->name, new_channel->description);
}

static void handle_create_thread(list_args_t* args)
{
    team_t* team = find_team_by_uuid(args->db, args->client->current_team_uuid);
    if (team == NULL) {
        dprintf(args->client->socket_fd, UNKNOWN_TEAM_RESP, UNKNOWN_TEAM,
        args->client->current_team_uuid);
        return;
    }
    channel_t* channel =
        find_channel_by_uuid(args->db, args->client->current_channel_uuid);
    if (channel == NULL) {
        send_error(args->client->socket_fd, UNKNOWN_CHANNEL, "Unknown channel");
        return;
    }
    create_thread_params_t params = init_create_thread_params(args);
    thread_t* new_thread = create_thread(args->db, &params);
    if (!new_thread)
        send_error(args->client->socket_fd, INTERNAL_SERVER_ERROR,
        "Thread not created");
    dprintf(args->client->socket_fd, CREATE_THREAD_RESP, THREAD_CREATED,
    new_thread->uuid, new_thread->title, new_thread->message,
    new_thread->related_channel_uuid, new_thread->creator_uuid,
    (long)new_thread->created_at);
}

static void handle_create_reply(list_args_t* args)
{
    team_t* team = find_team_by_uuid(args->db, args->client->current_team_uuid);
    if (team == NULL) {
        dprintf(args->client->socket_fd, UNKNOWN_TEAM_RESP, UNKNOWN_TEAM,
        args->client->current_team_uuid);
        return;
    }
    channel_t* channel =
        find_channel_by_uuid(args->db, args->client->current_channel_uuid);
    if (channel == NULL) {
        dprintf(args->client->socket_fd, UNKNOWN_CHANNEL_RESP, UNKNOWN_CHANNEL, args->client->current_channel_uuid);
        return;
    }
    thread_t* thread =
        find_thread_by_uuid(args->db, args->client->current_thread_uuid);
    if (thread == NULL) {
        dprintf(args->client->socket_fd, UNKNOWN_THREAD_RESP, UNKNOWN_THREAD, args->client->current_thread_uuid);
        return;
    }
    // CHECK RELATION IS CHANEL RELATED TO TEAMS
    reply_t* new_reply = add_reply_to_thread(
        args->db, args->client->current_team_uuid, args->split_command[2]);

    if (new_reply == NULL) {
        send_error(args->client->socket_fd, INTERNAL_SERVER_ERROR,
        "Reply not created");
        return;
    }
    dprintf(args->client->socket_fd, CREATED_REPLY_RESP, THREAD_REPLY_CREATED,
    new_reply->uuid, new_reply->body, (long)new_reply->created_at);
}

void create(list_args_t* args)
{
    switch (args->client->use_args_count) {
        case 0:
            handle_create_team(args);
            break;
        case 1:
            handle_create_channel(args);
            break;
        case 2:
            handle_create_thread(args);
            break;
        case 3:
            handle_create_reply(args);
            break;
        default:
            break;
    }
}
