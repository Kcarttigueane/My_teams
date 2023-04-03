/*
** EPITECH PROJECT, 2022
** B-NWP-400-LYN-4-1-myteams-jules.dutel
** File description:
** reply_created_notification.c
*/

#include "../../include/client.h"

void reply_created_notification(__attribute_maybe_unused__ char* json_response)
{
    char creator_uuid[MAX_UUID_LENGTH] = {0};
    char reply_body[MAX_BODY_LENGTH] = {0};
    char thread_uuid[MAX_UUID_LENGTH] = {0};
    char timestamp[MAX_TIMESTAMP_LENGTH] = {0};

    if (!extract_value("creator_uuid", json_response, creator_uuid,
        sizeof(creator_uuid)) ||
        !extract_value("reply_body", json_response, reply_body,
        sizeof(reply_body)) ||
        !extract_value("thread_uuid", json_response, thread_uuid,
        sizeof(thread_uuid)) ||
        !extract_value("timestamp", json_response, timestamp,
        sizeof(timestamp))) {
        printf("Error: invalid JSON format\n");
        return;
    }

    client_print_reply_created(thread_uuid, creator_uuid, (time_t)timestamp,
    reply_body);
}
