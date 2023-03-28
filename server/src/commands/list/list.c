/*
** EPITECH PROJECT, 2022
** MyTeams
** File description:
** list.c
*/

#include "../../../include/server.h"

void list(list_args_t* args)
{
    printf("LIST\n");

    if (args->client->use_args_count == FAILURE) {
        dprintf(args->client->socket_fd, "530 User the endpoint /use first\n");
        return;
    }

    if (args->client->use_args_count == 0) {
        dprintf(args->client->socket_fd, "200");
        list_teams(args->db);
        args->client->use_args_count = FAILURE;
    }
    if (args->client->use_args_count == 1) {
        dprintf(args->client->socket_fd, "200");
        list_channels(args->db);
        args->client->use_args_count = FAILURE;
    }
    if (args->client->use_args_count == 2) {
        dprintf(args->client->socket_fd, "200");
        list_threads(args->db);
        args->client->use_args_count = FAILURE;
    }
    if (args->client->use_args_count == 3) {
        dprintf(args->client->socket_fd, "200");
        list_replies_for_thread(args->db, args->split_command[3]);
        args->client->use_args_count = FAILURE;
    }
}
