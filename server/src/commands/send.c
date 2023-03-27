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

    remove_quotes(args->split_command[1]);
    if (find_user_by_uuid(args->db, args->split_command[1]) == NULL) {
        send_json_error_response(args->client->client_socket_fd, 530, "User not found");
        return;
    }

    discussion_t* dis = create_discussion(args->db,args->split_command[1],
                                          args->client->current_user_uuid);

    if (dis == NULL) {
        send_json_error_response(args->client->client_socket_fd, 530,
                                 "Impossible to create discussion");
        return;
    }

    if (add_message_to_discussion(args->db, args->client->current_user_uuid,
        args->split_command[1], args->split_command[2]) == false) {
        send_json_error_response(args->client->client_socket_fd, 530, "Message not sent");
        return;
    }

    // int server_event_private_message_sended(args->split_command[1], args->client->current_user_uuid, args->split_command[2]);

    dprintf(args->client->client_socket_fd, SEND_MSG_JSON_REP, args->split_command[1], args->split_command[2]);

    printf("Message sent to discussion %s\n", args->split_command[1]);
}
