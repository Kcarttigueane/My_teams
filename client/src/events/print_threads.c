/*
** EPITECH PROJECT, 2022
** B-NWP-400-LYN-4-1-myteams-jules.dutel
** File description:
** print_threads.c
*/

#include "../../include/client.h"

static bool thread_parsing(char* ptr)
{
    char thread_uuid[MAX_UUID_LENGTH] = {0};
    char thread_title[MAX_NAME_LENGTH] = {0};
    char thread_message[MAX_BODY_LENGTH] = {0};
    char creator_uuid[MAX_UUID_LENGTH] = {0};
    char timestamp[MAX_TIMESTAMP_LENGTH] = {0};
    extract_value("thread_uuid", ptr, thread_uuid, MAX_UUID_LENGTH);
    extract_value("thread_title", ptr, thread_title, MAX_NAME_LENGTH);
    extract_value("thread_message", ptr, thread_message, MAX_BODY_LENGTH);
    extract_value("creator_uuid", ptr, creator_uuid, MAX_UUID_LENGTH);
    extract_value("timestamp", ptr, timestamp, MAX_TIMESTAMP_LENGTH);

    if (!(*thread_uuid != '\0' && *thread_title != '\0' &&
        *thread_message != '\0' && *creator_uuid != '\0' &&
        *timestamp != '\0'))
        return false;

    time_t time = string_to_timestamp(timestamp);
    client_channel_print_threads(thread_uuid, creator_uuid, time, thread_title,
    thread_message);
    return true;
}

void print_threads(char* json_response)
{
    char* ptr = strstr(json_response, "\"threads\": [");
    if (!ptr) {
        printf("Error: threads not found\n");
        return;
    }
    ptr += strlen("\"threads\": [");

    while (ptr != NULL && *ptr != ']') {
        if (*ptr == ',')
            ptr++;

        if (!thread_parsing(ptr))
            break;

        ptr = strstr(ptr, "},");

        if (ptr != NULL)
            ptr += 2;
    }
}
