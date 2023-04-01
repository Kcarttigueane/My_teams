/*
** EPITECH PROJECT, 2022
** B-NWP-400-LYN-4-1-myteams-jules.dutel
** File description:
** print_channels.c
*/

#include "../../include/client.h"

void print_channels(char* json_response)
{
    char* ptr = strstr(json_response, "\"channels\": [");
    if (ptr == NULL) {
        printf("Error: channels not found\n");
        return;
    }
    ptr += strlen("\"channels\": [");
    while (ptr != NULL && *ptr != ']') {
        if (*ptr == ',') ptr++;
        char channel_uuid[MAX_UUID_LENGTH] = {0};
        char channel_name[MAX_NAME_LENGTH] = {0};
        char channel_desc[MAX_DESCRIPTION_LENGTH] = {0};
        if (!extract_value("channel_uuid", ptr, channel_uuid,
            sizeof(channel_uuid))) break;
        if (!extract_value("channel_name", ptr, channel_name,
            sizeof(channel_name))) break;
        if (!extract_value("channel_description", ptr, channel_desc,
            sizeof(channel_desc))) break;
        client_team_print_channels(channel_uuid, channel_name, channel_desc);
        ptr = strstr(ptr, "},");
        if (ptr != NULL) ptr += 2;
    }
}
