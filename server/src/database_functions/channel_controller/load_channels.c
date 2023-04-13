/*
** EPITECH PROJECT, 2022
** MyTeams
** File description:
** load_channels.c
*/

#include "../../../include/server.h"

static bool channel_parsing(database_t* db, char* ptr,
channel_t** current_channel)
{
    *current_channel = calloc(1, sizeof(channel_t));
    if (!*current_channel) return false;

    char timestamp[MAX_TIMESTAMP_LENGTH] = {0};

    extract_value("uuid", ptr, (*current_channel)->uuid, MAX_UUID_LENGTH);
    extract_value("name", ptr, (*current_channel)->name, MAX_NAME_LENGTH);
    extract_value("description", ptr, (*current_channel)->description,
    MAX_DESCRIPTION_LENGTH);
    extract_value("team_uuid", ptr, (*current_channel)->team_uuid,
    MAX_UUID_LENGTH);
    extract_value("creator_uuid", ptr, (*current_channel)->creator_uuid,
    MAX_UUID_LENGTH);
    extract_value("created_at", ptr, timestamp, MAX_TIMESTAMP_LENGTH);
    (*current_channel)->created_at = string_to_timestamp(timestamp);

    debug_channel(*current_channel);
    LIST_INSERT_HEAD(&db->channels, *current_channel, entries);
    return true;
}

bool parse_channel_json(database_t* db, char* json)
{
    LIST_INIT(&db->channels);

    char* ptr = strstr(json, "[");

    ptr += strlen("[");

    channel_t* current_channel = NULL;

    while (ptr != NULL && *ptr != ']') {
        if (*ptr == ',')
            ptr++;
        if (!channel_parsing(db, ptr, &current_channel))
            return false;
        ptr = strstr(ptr, "},");
        if (ptr != NULL)
            ptr += 2;
    }

    return true;
}

void load_channels_from_file(database_t* db)
{
    FILE* file = fopen("libs/database/channels.json", "r");

    if (!file) return;

    char* buffer = read_file_contents(file);

    if (!buffer) {
        fclose(file);
        return;
    }

    bool success = parse_channel_json(db, buffer);

    if (!success) {
        fclose(file);
        free(buffer);
        return;
    }
    fclose(file);
    free(buffer);
}
