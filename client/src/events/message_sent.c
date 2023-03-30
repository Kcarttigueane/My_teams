/*
** EPITECH PROJECT, 2022
** B-NWP-400-LYN-4-1-myteams-jules.dutel
** File description:
** message_sent.c
*/

#include "../../include/client.h"

void message_sent(char* json_response)
{
    char* recipient_uuid = json_get_value(json_response, "recipient_uuid");
    char* message_body = json_get_value(json_response, "message_body");

    if (recipient_uuid == NULL || message_body == NULL) {
        printf("Error: invalid JSON format\n");
        return;
    }

    client_event_private_message_received(recipient_uuid, message_body);

    free(recipient_uuid);
    free(message_body);
}
