/*
** EPITECH PROJECT, 2022
** MyTeams
** File description:
** user.c
*/

#include "../../include/server.h"

void user(list_args_t* args)
{
    printf("USER\r\n");

    user_t* user = find_user_by_uuid(args->db, args->split_command[1]);

    if (user == NULL) {
        dprintf(args->client->client_socket_fd, "530 User not found");
        return;
    }

    dprintf(args->client->client_socket_fd, "200 %s %s", user->uuid,
    user->username);
}
