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

    remove_quotes(args->split_command[1]);

    user_t* user = find_user_by_uuid(args->db, args->split_command[1]);

    if (user == NULL) {
        send_json_error_response(args->client->client_socket_fd, 530, "User not found");
        return;
    }

    dprintf(args->client->client_socket_fd, USER_DETAILS, user->username,
    user->uuid);
}
