/*
** EPITECH PROJECT, 2022
** B-NWP-400-LYN-4-1-myteams-jules.dutel
** File description:
** thread_created_notification.c
*/

#include "../../include/client.h"

void thread_created_notification(char* json_resp)
{
    char thread_uuid[MAX_UUID_LENGTH] = {0};
    char thread_title[MAX_NAME_LENGTH] = {0};
    char thread_message[MAX_DESCRIPTION_LENGTH] = {0};
    char creator_uuid[MAX_UUID_LENGTH] = {0};
    char timestamp[MAX_TIMESTAMP_LENGTH] = {0};
    if (!extract_value("thread_uuid", json_resp, thread_uuid,
        sizeof(thread_uuid)) ||
        !extract_value("thread_title", json_resp, thread_title,
        sizeof(thread_title)) ||
        !extract_value("thread_message", json_resp, thread_message,
        sizeof(thread_message)) ||
        !extract_value("creator_uuid", json_resp, creator_uuid,
        sizeof(creator_uuid)) ||
        !extract_value("timestamp", json_resp, timestamp, sizeof(timestamp))) {
        printf("Error: invalid JSON format\n");
        return;
    }
    time_t time = string_to_timestamp(timestamp);
    client_print_thread_created(thread_uuid, creator_uuid, time, thread_title,
    thread_message);
}
