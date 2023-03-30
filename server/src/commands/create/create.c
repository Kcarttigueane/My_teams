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
    create_channel_params_t params = {0};

    strcpy(params.name, args->split_command[1]);
    strcpy(params.description, args->split_command[2]);
    strcpy(params.team_uuid, args->client->current_team_uuid);
    strcpy(params.creator_uuid, args->client->current_user_uuid);

    channel_t* new_channel = create_channel(args->db, &params);

    if (!new_channel)
        send_error(args->client->socket_fd, INTERNAL_SERVER_ERROR,
        "Channel not created");

    dprintf(args->client->socket_fd, CREATE_CHANNEL_RESP, CHANNEL_CREATED,
    new_channel->uuid, new_channel->name, new_channel->description);
}

static void handle_create_thread(list_args_t* args)
{
    create_thread_params_t params = {0};

    strcpy(params.title, args->split_command[1]);
    strcpy(params.message, args->split_command[2]);
    strcpy(params.related_channel_uuid, args->client->current_channel_uuid);
    strcpy(params.creator_uuid, args->client->current_user_uuid);

    thread_t* new_thread = create_thread(args->db, &params);

    if (!new_thread)
        send_error(args->client->socket_fd, INTERNAL_SERVER_ERROR,
        "Thread not created");

    dprintf(args->client->socket_fd, CREATE_THREAD_RESP, THREAD_CREATED,
    new_thread->uuid, new_thread->title, new_thread->message);
}

static void handle_create_reply(list_args_t* args)
{
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
