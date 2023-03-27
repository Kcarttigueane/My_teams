/*
** EPITECH PROJECT, 2022
** MyTeams
** File description:
** users.c
*/

#include "../../include/server.h"

void users(list_args_t* args)
{
    char* json_users_response = print_users(args->db);

    send(args->client->client_socket_fd, json_users_response,
    strlen(json_users_response), 0);
}
