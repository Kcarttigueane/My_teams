/*
** EPITECH PROJECT, 2022
** B-NWP-400-LYN-4-1-myteams-jules.dutel
** File description:
** message_received.c
*/

#include "../../include/client.h"

void message_received(char* json_response)
{
    char recipient_uuid[MAX_UUID_LENGTH] = {0};
    char message_body[MAX_BODY_LENGTH] = {0};

    if (!extract_value("recipient_uuid", json_response, recipient_uuid,
        sizeof(recipient_uuid)) ||
        !extract_value("message_body", json_response, message_body,
        sizeof(message_body))) {
        printf("Error: invalid JSON format\n");
        return;
    }

    client_event_private_message_received(recipient_uuid, message_body);
}
