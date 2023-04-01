/*
** EPITECH PROJECT, 2022
** B-NWP-400-LYN-4-1-myteams-jules.dutel
** File description:
** print_threads.c
*/

#include "../../include/client.h"

void print_threads(char* json_response)
{
    char* ptr = strstr(json_response, "\"threads\": [");
    if (ptr == NULL) {
        printf("Error: threads not found\n");
        return;
    }
    ptr += strlen("\"threads\": [");
    while (ptr != NULL && *ptr != ']') {
        if (*ptr == ',') ptr++;
        char thread_uuid[MAX_UUID_LENGTH] = {0};
        char thread_title[MAX_NAME_LENGTH] = {0};
        char thread_message[MAX_BODY_LENGTH] = {0};
        char creator_uuid[MAX_UUID_LENGTH] = {0};
        char timestamp[30] = {0};
        if (!extract_value("thread_uuid", ptr, thread_uuid,
            sizeof(thread_uuid))) break;
        if (!extract_value("thread_title", ptr, thread_title,
            sizeof(thread_title))) break;
        if (!extract_value("thread_message", ptr, thread_message,
            sizeof(thread_message))) break;
        if (!extract_value("creator_uuid", ptr, creator_uuid,
            sizeof(creator_uuid))) break;
        if (!extract_value("timestamp", ptr, timestamp, sizeof(timestamp)))
            break;
        client_channel_print_threads(thread_uuid, creator_uuid, (time_t)timestamp,
        thread_title, thread_message);
        ptr = strstr(ptr, "},");
        if (ptr != NULL) ptr += 2;
    }
}
