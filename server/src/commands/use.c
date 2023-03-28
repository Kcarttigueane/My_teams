/*
** EPITECH PROJECT, 2022
** MyTeams
** File description:
** use.c
*/

#include "../../include/server.h"

void use(list_args_t* args)
{
    printf("USE\r\n");

    int size = get_size_word_array(args->split_command) - 1;

    if (size == 0) {
        printf("/user => without args called\n");
        args->client->use_args_count = 0;
    }
    if (size == 1) {
        printf("/user => without 1 args called\n");

        remove_quotes(args->split_command[1]);
        if (!is_team_exists(args->db, args->split_command[1])) {
            printf("Team %s does not exist\n", args->client->current_team_uuid);
            args->client->use_args_count = FAILURE;
            return;
        }
        strcpy(args->client->current_team_uuid, args->split_command[1]);
        args->client->use_args_count = 1;
    }
    if (size == 2) {
        printf("/user => without 2 args called\n");

        remove_quotes(args->split_command[1]);
        remove_quotes(args->split_command[2]);
        if (!is_team_exists(args->db, args->split_command[1])) {
            printf("Team %s does not exist\n", args->split_command[1]);
            args->client->use_args_count = FAILURE;
            return;
        }

        if (!is_channel_exist(args->db, args->split_command[2])) {
            printf("Channel %s does not 'exist\n", args->split_command[2]);
            args->client->use_args_count = FAILURE;
            return;
        }
        strcpy(args->client->current_team_uuid, args->split_command[1]);
        strcpy(args->client->current_channel_uuid, args->split_command[2]);
        args->client->use_args_count = 2;
    }

    if (size == 3) {
        printf("/user => without 3 args called\n");

        remove_quotes(args->split_command[1]);
        remove_quotes(args->split_command[2]);
        remove_quotes(args->split_command[3]);
        if (!is_team_exists(args->db, args->split_command[1])) {
            printf("Team %s does not exist\n", args->split_command[1]);
            args->client->use_args_count = FAILURE;
            return;
        }

        if (!is_channel_exist(args->db, args->split_command[2])) {
            printf("Channel %s does not 'exist\n", args->split_command[2]);
            args->client->use_args_count = FAILURE;
            return;
        }

        // if (!is_thread_exist(args->db, args->split_command[3])) {
        //     printf("Thread %s does not exist\n", args->split_command[3]);
        //     args->client->use_args_count = FAILURE;
        //     return;
        // }
        strcpy(args->client->current_team_uuid, args->split_command[1]);
        strcpy(args->client->current_channel_uuid, args->split_command[2]);
        strcpy(args->client->current_thread_uuid, args->split_command[3]);

        args->client->use_args_count = 2;
    }

    dprintf(args->client->socket_fd, "200 Command use called\n");
}
