/*
** EPITECH PROJECT, 2022
** MyTeams
** File description:
** msgs.c
*/

#include "../../include/server.h"

void msgs(list_args_t* args)
{
    printf("SEND\r\n");

    discussion_t* discussion = find_discussion_by_users(
        args->db, args->client->current_user_uuid, args->split_command[1]);

    if (discussion == NULL) {
        dprintf(args->client->client_socket_fd, "530 Discussion not found");
        return;
    }

    // maximum 100 messages, each with a body of length MAX_BODY_LENGTH
    char message_list[MAX_BODY_LENGTH * 100];

    // initialize the message list to empty
    memset(message_list, 0, sizeof(message_list));

    // Concatenate all messages in the discussion into a single string
    message_t* message;
    LIST_FOREACH(message, &(discussion->messages), entries)
    {
        char formatted_message[MAX_BODY_LENGTH + MAX_UUID_STR_LEN];
        sprintf(formatted_message, "%s: %s", message->uuid, message->body);
        strcat(message_list, formatted_message);
    }

    send(args->client->client_socket_fd, message_list, strlen(message_list), 0);
}

