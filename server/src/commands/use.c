/*
** EPITECH PROJECT, 2022
** MyTeams
** File description:
** use.c
*/

#include "../../include/server.h"

static void handle_use_one_arg(list_args_t* args)
{
    if (strlen(args->split_command[1]) != MAX_UUID_LENGTH) {
        send_error(args->client->socket_fd, UNKNOWN_TEAM, "Invalid UUID");
        return;
    }

    strcpy(args->client->current_team_uuid, args->split_command[1]);
    args->client->use_args_count = 1;
}

static void handle_use_two_args(list_args_t* args)
{
    if (strlen(args->split_command[1]) != MAX_UUID_LENGTH) {
        send_error(args->client->socket_fd, UNKNOWN_TEAM, "Invalid UUID");
        return;
    }

    if (strlen(args->split_command[2]) != MAX_UUID_LENGTH) {
        send_error(args->client->socket_fd, UNKNOWN_CHANNEL, "Invalid UUID");
        return;
    }

    strcpy(args->client->current_team_uuid, args->split_command[1]);
    strcpy(args->client->current_channel_uuid, args->split_command[2]);
    args->client->use_args_count = 2;
}

static void handle_use_three_args(list_args_t* args)
{
    if (strlen(args->split_command[1]) != MAX_UUID_LENGTH) {
        send_error(args->client->socket_fd, UNKNOWN_TEAM, "Invalid UUID");
        return;
    }

    if (strlen(args->split_command[2]) != MAX_UUID_LENGTH) {
        send_error(args->client->socket_fd, UNKNOWN_CHANNEL, "Invalid UUID");
        return;
    }

    if (strlen(args->split_command[3]) != MAX_UUID_LENGTH) {
        send_error(args->client->socket_fd, UNKNOWN_THREAD, "Invalid UUID");
        return;
    }

    strcpy(args->client->current_team_uuid, args->split_command[1]);
    strcpy(args->client->current_channel_uuid, args->split_command[2]);
    strcpy(args->client->current_thread_uuid, args->split_command[3]);
    args->client->use_args_count = 3;
}

void use(list_args_t* args)
{
    int size = get_size_word_array(args->split_command) - 1;

    switch (size) {
        case 0:
            args->client->use_args_count = 0;
            break;
        case 1:
            handle_use_one_arg(args);
            break;
        case 2:
            handle_use_two_args(args);
            break;
        case 3:
            handle_use_three_args(args);
            break;
        default:
            break;
    }
}
