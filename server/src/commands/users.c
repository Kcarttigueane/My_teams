/*
** EPITECH PROJECT, 2022
** MyTeams
** File description:
** users.c
*/

#include "../../include/server.h"

void users(list_args_t* args)
{
    char* json_users_resp = print_users(args->db);

    send(args->client->socket_fd, json_users_resp, strlen(json_users_resp), 0);

    free(json_users_resp);
}
