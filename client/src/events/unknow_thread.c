/*
** EPITECH PROJECT, 2022
** B-NWP-400-LYN-4-1-myteams-jules.dutel
** File description:
** unknow_thread.c
*/

#include "../../include/client.h"

void unknow_thread(char* json_response)
{
    char thread_uuid[MAX_UUID_LENGTH] = {0};

    if (!extract_value("thread_uuid", json_response, thread_uuid,
        sizeof(thread_uuid))) {
        printf("Error: invalid JSON format\n");
        return;
    }

    client_error_unknown_thread(thread_uuid);
}
