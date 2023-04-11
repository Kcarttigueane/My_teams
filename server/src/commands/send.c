/*
** EPITECH PROJECT, 2022
** MyTeams
** File description:
** send.c
*/

#include "../../include/server.h"

static bool error_handling_send(list_args_t *args, char *receiver_uuid,
char *message)
{
    if (strlen(receiver_uuid) != (MAX_UUID_LENGTH - 1)) {
        send_error(args->client->socket_fd, UNKNOWN_USER, "Invalid UUID");
        return false;
    }

    if (strlen(message) > MAX_BODY_LENGTH) {
        send_error(args->client->socket_fd, INTERNAL_SERVER_ERROR,
        "Message too long");
        return false;
    }
    return true;
}

static bool validate_receiver(list_args_t* args, char* receiver_uuid)
{
    if (find_user_by_uuid(args->db, receiver_uuid) == NULL) {
        dprintf(args->client->socket_fd, UNKNOWN_USER_RESP, UNKNOWN_USER,
        receiver_uuid);
        return false;
    }
    return true;
}

static discussion_t* create_new_discussion(list_args_t* args,
char* receiver_uuid)
{
    discussion_t* dis = create_discussion(args->db, receiver_uuid,
    args->client->current_user_uuid);

    if (dis == NULL) {
        send_error(args->client->socket_fd, INTERNAL_SERVER_ERROR,
        "Impossible to create discussion");
    }
    return dis;
}

static bool try_add_message(list_args_t* args, char* receiver_uuid,
char* message)
{
    if (!add_message_to_discussion(args->db, args->client->current_user_uuid,
        receiver_uuid, message)) {
        send_error(args->client->socket_fd, 530, "Message not sent");
        return false;
    }
    return true;
}

void send_msg(list_args_t* args)
{
    char* receiver_uuid = args->split_command[1];
    char* message = args->split_command[2];

    if (!error_handling_send(args, receiver_uuid, message)) return;
    if (!validate_receiver(args, receiver_uuid)) return;
    discussion_t* dis = create_new_discussion(args, receiver_uuid);
    if (!dis) return;
    if (!try_add_message(args, receiver_uuid, message)) return;

    server_event_private_message_sended(args->client->current_user_uuid,
    receiver_uuid, message);

    clients_t* receiver = find_client_by_uuid(args->clients, receiver_uuid);
    if (receiver != NULL)
        dprintf(receiver->socket_fd, SEND_MSG_JSON_RESP, MESSAGE_RECEIVED,
        args->client->current_user_uuid, message);
}
