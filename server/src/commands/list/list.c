/*
** EPITECH PROJECT, 2022
** MyTeams
** File description:
** list.c
*/

#include "../../../include/server.h"

static void handle_list_teams(list_args_t* args)
{
    char* json_response = list_teams(args->db);

    if (!json_response) {
        send_error(args->client->socket_fd, UNKNOWN_TEAM, "No teams found");
        return;
    }

    send(args->client->socket_fd, json_response, strlen(json_response), 0);
    free(json_response);
}

static void handle_list_channels(list_args_t* args)
{
    team_t* team = find_team_by_uuid(args->db, args->client->current_team_uuid);

    if (!team) {
        dprintf(args->client->socket_fd, UNKNOWN_TEAM_RESP, UNKNOWN_TEAM,
        args->client->current_team_uuid);
        return;
    }

    char* json_response =
        list_channels(args->db, args->client->current_team_uuid);

    if (!json_response) {
        send_error(args->client->socket_fd, UNKNOWN_CHANNEL, "Team not found");
        return;
    }

    send(args->client->socket_fd, json_response, strlen(json_response), 0);
    free(json_response);
}

static void handle_list_threads(list_args_t* args)
{
    team_t* team;
    channel_t* channel;

    if (!validate_team_channel(args, &team, &channel))
        return;

    char* json_response =
        list_threads(args->db, args->client->current_channel_uuid);

    if (!json_response) {
        send_error(args->client->socket_fd, UNAUTHORIZED, "Channel not found");
        return;
    }

    send(args->client->socket_fd, json_response, strlen(json_response), 0);
    free(json_response);
}

static void handle_list_replies(list_args_t* args)
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
    char* json_response =
        list_replies_for_thread(args->db, args->client->current_thread_uuid);
    if (!json_response) {
        send_error(args->client->socket_fd, INTERNAL_SERVER_ERROR,
        "Malloc failed");
        return;
    }

    send(args->client->socket_fd, json_response, strlen(json_response), 0);
    free(json_response);
}

void list(list_args_t* args)
{
    switch (args->client->use_args_count) {
        case 0:
            handle_list_teams(args);
            break;
        case 1:
            handle_list_channels(args);
            break;
        case 2:
            handle_list_threads(args);
            break;
        case 3:
            handle_list_replies(args);
            break;
        default:
            send_error(args->client->socket_fd, INTERNAL_SERVER_ERROR,
            "Use /use command first");
            break;
    }
    args->client->use_args_count = FAILURE;
}
