/*
** EPITECH PROJECT, 2022
** B-NWP-400-LYN-4-1-myteams-jules.dutel
** File description:
** channel_created_notification.c
*/

#include "../../include/client.h"

void channel_created_notification(char* json_response)
{
    char* channel_uuid = json_get_value(json_response, "channel_uuid");
    char* channel_name = json_get_value(json_response, "channel_name");
    char* channel_description =
        json_get_value(json_response, "channel_description");

    if (channel_uuid == NULL || channel_name == NULL ||
        channel_description == NULL) {
        printf("Error: Failed to get channel information\n");
        return;
    }

    client_print_channel_created(channel_uuid, channel_name,
    channel_description);

    free(channel_uuid);
    free(channel_name);
    free(channel_description);
}
