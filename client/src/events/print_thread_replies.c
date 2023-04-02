/*
** EPITECH PROJECT, 2022
** B-NWP-400-LYN-4-1-myteams-jules.dutel
** File description:
** print_thread_replies.c
*/

#include "../../include/client.h"

void print_thread_replies(__attribute_maybe_unused__ char* json_response)
{
    char* ptr = strstr(json_response, "\"replies\": [");
    if (ptr == NULL) {
        printf("Error: replies not found\n");
        return;
    }
    ptr += strlen("\"replies\": [");
    while (ptr != NULL && *ptr != ']') {
        if (*ptr == ',')  ptr++;
        char thread_uuid[MAX_UUID_LENGTH] = {0};
        char reply_body[MAX_BODY_LENGTH] = {0};
        char creator_uuid[MAX_UUID_LENGTH] = {0};
        char timestamp[30] = {0};
        if (!extract_value("thread_uuid", ptr, thread_uuid,
            sizeof(thread_uuid)))
            break;
        if (!extract_value("reply_body", ptr, reply_body,
            sizeof(reply_body)))
            break;
        if (!extract_value("creator_uuid", ptr, creator_uuid,
            sizeof(creator_uuid)))
            break;
        if (!extract_value("timestamp", ptr, timestamp, sizeof(timestamp)))
            break;
        client_thread_print_replies(thread_uuid, creator_uuid,
        atoi(timestamp), reply_body);
        ptr = strstr(ptr, "},");
        if (ptr != NULL) ptr += 2;
    }
}
