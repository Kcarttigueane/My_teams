/*
** EPITECH PROJECT, 2022
** MyTeams
** File description:
** help.c
*/

#include "../../include/server.h"

void help(list_args_t* args)
{
    dprintf(args->client->socket_fd, "%s", HELP_JSON_RESP);
}
