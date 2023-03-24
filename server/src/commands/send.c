/*
** EPITECH PROJECT, 2022
** MyTeams
** File description:
** send.c
*/

#include "../../include/server.h"

void send_msg(list_args_t* args)
{
    printf("SEND\r\n");

    discussion_t* dis = create_discussion(args->db, args->split_command[1],
    args->client->current_user_uuid);

    if (dis == NULL) {
        dprintf(args->client->client_socket_fd, "530 Discussion not found");
        return;
    }

    if (add_message_to_discussion(args->db, args->client->current_user_uuid,
    args->split_command[2], args->split_command[3]) == false) {
        dprintf(args->client->client_socket_fd, "530 Message not sent");
        return;
    }

    dprintf(args->client->client_socket_fd, "200");
    printf("Message sent to discussion %s\n", args->split_command[1]);
}
