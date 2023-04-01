/*
** EPITECH PROJECT, 2022
** B-NWP-400-LYN-4-1-myteams-jules.dutel
** File description:
** print_messages.c
*/

#include "../../include/client.h"

void print_messages(char* json_response)
{
    char* ptr = strstr(json_response, "\"messages\": [");
    if (ptr == NULL) {
        printf("Error: messages not found\n");
        return;
    }
    ptr += strlen("\"messages\": [");
    while (ptr != NULL && *ptr != ']') {
        if (*ptr == ',') ptr++;
        char message_body[MAX_BODY_LENGTH] = {0};
        char timestamp[30] = {0};
        char sender_uuid[MAX_UUID_LENGTH] = {0};
        if (!extract_value("message_body", ptr, message_body,
            sizeof(message_body))) break;
        if (!extract_value("timestamp", ptr, timestamp, sizeof(timestamp)))
            break;
        if (!extract_value("sender_uuid", ptr, sender_uuid,
            sizeof(sender_uuid))) break;
        client_private_message_print_messages(sender_uuid, (time_t)timestamp,
        message_body);
        ptr = strstr(ptr, "},");
        if (ptr != NULL) ptr += 2;
    }
}
