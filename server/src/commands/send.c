/*
** EPITECH PROJECT, 2022
** MyTeams
** File description:
** send.c
*/

#include "../../include/server.h"

void send_msg(list_args_t* args)
{
    remove_quotes(args->split_command[1]);
    remove_quotes(args->split_command[2]);
    if (find_user_by_uuid(args->db, args->split_command[1]) == NULL) {
        send_error(args->client->socket_fd, INTERNAL_SERVER_ERROR,
        "User not found");
        return;
    }
    discussion_t* dis = create_discussion(args->db, args->split_command[1],
    args->client->current_user_uuid);
    if (dis == NULL) {
        send_error(args->client->socket_fd, INTERNAL_SERVER_ERROR,
        "Impossible to create discussion");
        return;
    }
    if (add_message_to_discussion(args->db, args->client->current_user_uuid,
    args->split_command[1], args->split_command[2]) == false) {
        send_error(args->client->socket_fd, 530, "Message not sent");
        return;
    }
    dprintf(args->client->socket_fd, SEND_MSG_JSON_RESP, MESSAGE_SENT,
    args->client->current_user_uuid, args->split_command[2]);
    printf("Message sent to discussion %s\n", args->split_command[1]);
}
