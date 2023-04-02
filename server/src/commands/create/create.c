/*
** EPITECH PROJECT, 2022
** MyTeams
** File description:
** create.c
*/

#include "../../../include/server.h"

static void handle_create_team(list_args_t* args)
{
    char *team_name = args->split_command[1];
    char *team_description = args->split_command[2];

    team_t* new_teams = create_team(args->db, team_name, team_description);

    if (!new_teams)
        send_error(args->client->socket_fd, INTERNAL_SERVER_ERROR,
        "Team not created");

    team_creation_send_json_resp(args, new_teams);
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

    team_channel_send_json_resp(args, new_channel);
}

static void handle_create_thread(list_args_t* args)
{
    team_t* team;
    channel_t* channel;

    if (!validate_team_channel(args, &team, &channel))
        return;

    create_thread_params_t params = init_create_thread_params(args);
    thread_t* new_thread = create_thread(args->db, &params);

    if (!new_thread)
        send_error(args->client->socket_fd, INTERNAL_SERVER_ERROR,
        "Thread not created");

    thread_creation_send_json_resp(args, new_thread);
}

static void handle_create_reply(list_args_t* args)
{
    team_t* team;
    channel_t* channel;
    thread_t* thread;
    if (!validate_team_channel_thread(args, &team, &channel, &thread)) return;
    if (!is_thread_related_to_channel_to_team(team, channel, thread)) {
        dprintf(args->client->socket_fd, UNKNOWN_THREAD_RESP, UNKNOWN_THREAD,
        args->client->current_thread_uuid);
        return;
    }
    reply_t* new_reply = add_reply_to_thread(
        args->db, args->client->current_team_uuid, args->split_command[2]);
    if (new_reply == NULL) {
        send_error(args->client->socket_fd, INTERNAL_SERVER_ERROR,
        "Reply not created");
        return;
    }
    dprintf(args->client->socket_fd, CREATED_REPLY_RESP, THREAD_REPLY_CREATED,
    new_reply->uuid, new_reply->body, (long)new_reply->created_at);
    server_event_reply_created(thread->uuid, args->client->current_user_uuid,
    new_reply->body);
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
    args->client->use_args_count = FAILURE;
}
