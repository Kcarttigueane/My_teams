/*
** EPITECH PROJECT, 2022
** B-NWP-400-LYN-4-1-myteams-jules.dutel
** File description:
** print_messages.c
*/

#include "../../include/client.h"

static bool is_message_info_valid(char* message_body, char* timestamp,
char* sender_uuid)
{
    return *message_body != '\0' && *timestamp != '\0' && *sender_uuid != '\0';
}

static bool messages_parsing(char *ptr)
{
    char message_body[MAX_BODY_LENGTH] = {0};
    char timestamp[30] = {0};
    char sender_uuid[MAX_UUID_LENGTH] = {0};

    extract_value("message_body", ptr, message_body, MAX_BODY_LENGTH);
    extract_value("timestamp", ptr, timestamp, 30);
    extract_value("sender_uuid", ptr, sender_uuid, MAX_UUID_LENGTH);

    if (!is_message_info_valid(message_body, timestamp, sender_uuid))
        return false;

    client_private_message_print_messages(sender_uuid, (time_t)timestamp,
    message_body);

    return true;
}

void print_messages(char* json_response)
{
    char* ptr = strstr(json_response, "\"messages\": [");
    if (ptr == NULL) {
        printf("Error: messages not found\n");
        return;
    }
    ptr += strlen("\"messages\": [");
    while (ptr != NULL && *ptr != ']') {
        if (*ptr == ',')
            ptr++;
        if (!messages_parsing(ptr))
            break;
        ptr = strstr(ptr, "},");
        if (ptr != NULL)
            ptr += 2;
    }
}
