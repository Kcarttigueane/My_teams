/*
** EPITECH PROJECT, 2022
** B-NWP-400-LYN-4-1-myteams-jules.dutel
** File description:
** info_channel.c
*/

#include "../../include/client.h"

void info_channel(char* json_response)
{
    char *channel_uuid = json_get_value(json_response, "channel_uuid");
    char *channel_name = json_get_value(json_response, "channel_name");
    char *channel_description = json_get_value(json_response,
    "channel_description");

    if (!channel_uuid || !channel_name || !channel_description) {
        printf("Error: Failed to get channel information\n");
        return;
    }

    client_print_channel(channel_uuid, channel_name, channel_description);

    free(channel_uuid);
    free(channel_name);
    free(channel_description);
}
