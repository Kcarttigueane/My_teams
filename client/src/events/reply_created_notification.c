/*
** EPITECH PROJECT, 2022
** B-NWP-400-LYN-4-1-myteams-jules.dutel
** File description:
** reply_created_notification.c
*/

#include "../../include/client.h"

void reply_created_notification(__attribute_maybe_unused__ char* json_response)
{
    char* creator_uuid = json_get_value(json_response, "creator_uuid");
    char* reply_body = json_get_value(json_response, "reply_body");
    char* thread_uuid = json_get_value(json_response, "thread_uuid");
    char *timestamp = json_get_value(json_response, "timestamp");

    if (creator_uuid == NULL || reply_body == NULL || timestamp == NULL ||
        thread_uuid == NULL) {
        printf("Error: Invalid json response from server\n");
        return;
    }
    client_print_reply_created(thread_uuid, creator_uuid, (time_t)timestamp,
    reply_body);

    free(creator_uuid);
    free(reply_body);
    free(timestamp);
    free(thread_uuid);
}
