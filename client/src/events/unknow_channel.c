/*
** EPITECH PROJECT, 2022
** B-NWP-400-LYN-4-1-myteams-jules.dutel
** File description:
** unknow_channel.c
*/

#include "../../include/client.h"

void unknow_channel(char* json_response)
{
    char *channel_uuid = json_get_value(json_response, "channel_uuid");

    if (channel_uuid == NULL) {
        printf("Error: invalid JSON format\n");
        return;
    }

    client_error_unknown_channel(channel_uuid);

    free(channel_uuid);
}
