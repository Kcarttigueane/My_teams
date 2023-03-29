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
    list_channels(args->db);

    char* json_response = list_channels(args->db);

    if (!json_response) {
        return;
    }

    send(args->client->socket_fd, json_response, strlen(json_response), 0);
    free(json_response);
}
