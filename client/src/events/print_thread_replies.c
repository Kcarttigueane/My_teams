/*
** EPITECH PROJECT, 2022
** B-NWP-400-LYN-4-1-myteams-jules.dutel
** File description:
** print_thread_replies.c
*/

#include "../../include/client.h"

bool is_reply_info_valid(char* thread_uuid, char* reply_body,
char* creator_uuid, char* timestamp)
{
    return *thread_uuid != '\0' && *reply_body != '\0' &&
        *creator_uuid != '\0' && *timestamp != '\0';
}

static bool thread_replies_parsing(char *ptr)
{
    char thread_uuid[MAX_UUID_LENGTH] = {0};
    char reply_body[MAX_BODY_LENGTH] = {0};
    char creator_uuid[MAX_UUID_LENGTH] = {0};
    char timestamp[30] = {0};

    extract_value("thread_uuid", ptr, thread_uuid, MAX_UUID_LENGTH);
    extract_value("reply_body", ptr, reply_body, MAX_BODY_LENGTH);
    extract_value("creator_uuid", ptr, creator_uuid, MAX_UUID_LENGTH);
    extract_value("timestamp", ptr, timestamp, 30);

    if (!is_reply_info_valid(thread_uuid, reply_body, creator_uuid, timestamp))
        return false;

    time_t time = string_to_timestamp(timestamp);

    client_thread_print_replies(thread_uuid, creator_uuid, time, reply_body);

    return true;
}

void print_thread_replies(__attribute_maybe_unused__ char* json_response)
{
    char* ptr = strstr(json_response, "\"replies\": [");
    if (ptr == NULL) {
        printf("Error: replies not found\n");
        return;
    }
    ptr += strlen("\"replies\": [");
    while (ptr != NULL && *ptr != ']') {
        if (*ptr == ',')
            ptr++;
        if (!thread_replies_parsing(ptr))
            break;
        ptr = strstr(ptr, "},");
        if (ptr != NULL)
            ptr += 2;
    }
}
