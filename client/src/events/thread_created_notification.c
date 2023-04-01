/*
** EPITECH PROJECT, 2022
** B-NWP-400-LYN-4-1-myteams-jules.dutel
** File description:
** thread_created_notification.c
*/

#include "../../include/client.h"

void thread_created_notification(char* json_response)
{
    char* thread_uuid = json_get_value(json_response, "thread_uuid");
    char* thread_title = json_get_value(json_response, "thread_title");
    char* thread_message = json_get_value(json_response, "thread_message");
    char* creator_uuid = json_get_value(json_response, "creator_uuid");
    char* timestamp = json_get_value(json_response, "timestamp");

    if (thread_uuid == NULL || thread_title == NULL || thread_message == NULL ||
        creator_uuid == NULL || timestamp == NULL) {
        printf("Error: Failed to get thread information\n");
        return;
    }

    client_print_thread_created(thread_uuid, creator_uuid, (time_t)timestamp,
    thread_title, thread_message);

    free(thread_uuid);
    free(thread_title);
    free(thread_message);
    free(creator_uuid);
    free(timestamp);
}
