/*
** EPITECH PROJECT, 2022
** MyTeams
** File description:
** use.c
*/

#include "../../include/server.h"

static void handle_use_one_arg(list_args_t* args)
{
    strcpy(args->client->current_team_uuid, args->split_command[1]);
    args->client->use_args_count = 1;
}

static void handle_use_two_args(list_args_t* args)
{
    strcpy(args->client->current_team_uuid, args->split_command[1]);
    strcpy(args->client->current_channel_uuid, args->split_command[2]);
    args->client->use_args_count = 2;
}

static void handle_use_three_args(list_args_t* args)
{
    strcpy(args->client->current_team_uuid, args->split_command[1]);
    strcpy(args->client->current_channel_uuid, args->split_command[2]);
    strcpy(args->client->current_thread_uuid, args->split_command[3]);
    args->client->use_args_count = 3;
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
