/*
** EPITECH PROJECT, 2022
** MyTeams
** File description:
** send.c
*/

#include "../../include/server.h"

static bool validate_recipient(list_args_t* args, char* recipient_uuid)
{
    if (find_user_by_uuid(args->db, recipient_uuid) == NULL) {
        dprintf(args->client->socket_fd, UNKNOWN_USER_RESP, UNKNOWN_USER,
        recipient_uuid);
        return false;
    }
    return true;
}

static discussion_t* create_new_discussion(list_args_t* args,
char* recipient_uuid)
{
    discussion_t* dis = create_discussion(args->db, recipient_uuid,
    args->client->current_user_uuid);

    if (dis == NULL) {
        send_error(args->client->socket_fd, INTERNAL_SERVER_ERROR,
        "Impossible to create discussion");
    }
    return dis;
}

static bool try_add_message(list_args_t* args, char* recipient_uuid,
char* message)
{
    if (!add_message_to_discussion(args->db, args->client->current_user_uuid,
        recipient_uuid, message)) {
        send_error(args->client->socket_fd, 530, "Message not sent");
        return false;
    }
    return true;
}

void send_msg(list_args_t* args)
{
    remove_quotes(args->split_command[1]);
    remove_quotes(args->split_command[2]);
    char* recipient_uuid = args->split_command[1];
    char* message = args->split_command[2];

    if (!validate_recipient(args, recipient_uuid))
        return;

    discussion_t* dis = create_new_discussion(args, recipient_uuid);
    if (!dis) return;

    if (!try_add_message(args, recipient_uuid, message))
        return;

    dprintf(args->client->socket_fd, SEND_MSG_JSON_RESP, MESSAGE_SENT,
    args->client->current_user_uuid, message);

    server_event_private_message_sended(args->client->current_user_uuid,
    recipient_uuid, message);
}
