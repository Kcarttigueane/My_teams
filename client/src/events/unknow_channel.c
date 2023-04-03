/*
** EPITECH PROJECT, 2022
** B-NWP-400-LYN-4-1-myteams-jules.dutel
** File description:
** unknow_channel.c
*/

#include "../../include/client.h"

void unknow_channel(char* json_response)
{
    char channel_uuid[MAX_UUID_LENGTH] = {0};

    if (!extract_value("channel_uuid", json_response, channel_uuid,
        sizeof(channel_uuid))) {
        printf("Error: invalid JSON format\n");
        return;
    }

    client_error_unknown_channel(channel_uuid);
}
