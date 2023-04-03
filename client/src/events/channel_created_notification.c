/*
** EPITECH PROJECT, 2022
** B-NWP-400-LYN-4-1-myteams-jules.dutel
** File description:
** channel_created_notification.c
*/

#include "../../include/client.h"

void channel_created_notification(char* json_response)
{
    char channel_uuid[MAX_UUID_LENGTH] = {0};
    char channel_name[MAX_NAME_LENGTH] = {0};
    char channel_description[MAX_DESCRIPTION_LENGTH] = {0};

    if (!extract_value("channel_uuid", json_response, channel_uuid,
        sizeof(channel_uuid)) ||
        !extract_value("channel_name", json_response, channel_name,
        sizeof(channel_name)) ||
        !extract_value("channel_description", json_response,
        channel_description, sizeof(channel_description))) {
        printf("Error: invalid JSON format\n");
        return;
    }

    client_print_channel(channel_uuid, channel_name, channel_description);
}
