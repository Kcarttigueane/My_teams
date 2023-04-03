/*
** EPITECH PROJECT, 2022
** B-NWP-400-LYN-4-1-myteams-jules.dutel
** File description:
** print_channels.c
*/

#include "../../include/client.h"

bool is_channel_info_valid(char* channel_uuid, char* channel_name,
char* channel_desc)
{
    return *channel_uuid != '\0' && *channel_name != '\0' &&
    *channel_desc != '\0';
}

static bool channel_parsing(char* ptr)
{
    char channel_uuid[MAX_UUID_LENGTH] = {0};
    char channel_name[MAX_NAME_LENGTH] = {0};
    char channel_desc[MAX_DESCRIPTION_LENGTH] = {0};

    extract_value("channel_uuid", ptr, channel_uuid, MAX_UUID_LENGTH);
    extract_value("channel_name", ptr, channel_name, MAX_NAME_LENGTH);
    extract_value("channel_description", ptr, channel_desc,
    MAX_DESCRIPTION_LENGTH);

    if (!is_channel_info_valid(channel_uuid, channel_name, channel_desc))
        return false;

    client_team_print_channels(channel_uuid, channel_name, channel_desc);

    return true;
}

void print_channels(char* json_response)
{
    char* ptr = strstr(json_response, "\"channels\": [");

    if (ptr == NULL) {
        printf("Error: channels not found\n");
        return;
    }

    ptr += strlen("\"channels\": [");

    while (ptr != NULL && *ptr != ']') {
        if (*ptr == ',')
            ptr++;
        if (!channel_parsing(ptr))
            break;
        ptr = strstr(ptr, "},");
        if (ptr != NULL)
            ptr += 2;
    }
}
