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
        send_error(args->client->socket_fd, UNAUTHORIZED, "No teams found");
        return;
    }

    send(args->client->socket_fd, json_response, strlen(json_response), 0);
    free(json_response);
}

static void handle_list_channels(list_args_t* args)
{
    char* json_response =
        list_channels(args->db, args->client->current_team_uuid);

    if (!json_response) {
        send_error(args->client->socket_fd, UNAUTHORIZED, "Team not found");
        return;
    }

    send(args->client->socket_fd, json_response, strlen(json_response), 0);
    free(json_response);
}

static void handle_list_threads(list_args_t* args)
{
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
    char* json_response =
        list_replies_for_thread(args->db, args->client->current_thread_uuid);

    if (!json_response) {
        send_error(args->client->socket_fd, UNAUTHORIZED, "Thread not found");
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
            send_error(args->client->socket_fd, 400, "Too many arguments");
            break;
    }
}
