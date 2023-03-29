/*
** EPITECH PROJECT, 2022
** MyTeams
** File description:
** use.c
*/

#include "../../include/server.h"

void handle_use_one_arg(list_args_t* args)
{
    team_t* team = find_team_by_uuid(args->db, args->split_command[1]);

    if (team) {
        strcpy(args->client->current_team_uuid, args->split_command[1]);
        args->client->use_args_count = 1;
    } else {
        send_error(args->client->socket_fd, UNKNOWN_TEAM, "Unknown team");
    }
}

void handle_use_two_args(list_args_t* args)
{
    team_t* team = find_team_by_uuid(args->db, args->split_command[1]);
    channel_t* channel = find_channel_by_uuid(args->db, args->split_command[2]);

    if (team && channel && is_channel_related_to_team(team, channel)) {
        strcpy(args->client->current_team_uuid, args->split_command[1]);
        strcpy(args->client->current_channel_uuid, args->split_command[2]);
        args->client->use_args_count = 2;
    } else {
        send_error(args->client->socket_fd, UNKNOWN_CHANNEL, "Unknown channel");
    }
}

void handle_use_three_args(list_args_t* args)
{
    team_t* team = find_team_by_uuid(args->db, args->split_command[1]);
    channel_t* channel = find_channel_by_uuid(args->db, args->split_command[2]);
    thread_t* thread = find_thread_by_uuid(args->db, args->split_command[3]);

    if (team && channel && thread &&
        is_thread_related_to_channel_to_team(team, channel, thread)) {
        strcpy(args->client->current_team_uuid, args->split_command[1]);
        strcpy(args->client->current_channel_uuid, args->split_command[2]);
        strcpy(args->client->current_thread_uuid, args->split_command[3]);
        args->client->use_args_count = 3;
    } else {
        send_error(args->client->socket_fd, UNKNOWN_THREAD, "Unknown thread");
    }
}

void use(list_args_t* args)
{
    int size = get_size_word_array(args->split_command) - 1;
    remove_quotes(args->split_command[1]);
    if (size >= 2) remove_quotes(args->split_command[2]);
    if (size >= 3) remove_quotes(args->split_command[3]);
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
