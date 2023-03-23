/*
** EPITECH PROJECT, 2022
** MyTeams
** File description:
** send.c
*/

#include "../../include/server.h"

void send_msg(__attribute_maybe_unused__ list_args_t* args)
{
    printf("SEND\r\n");

    user_t* user = get_user_by_uuid(args->db->clients, args->split_command[1]);

    if (user == NULL) {
        dprintf(args->client->client_socket_fd, "530 User not found can't send message");
        return;
    }


}
