/*
** EPITECH PROJECT, 2022
** MyTeams
** File description:
** load_channels.c
*/

#include "../../../include/server.h"

static bool parse_user_uuid_in_channel(channel_t* current_channel,
int* user_count, char** users_start)
{
    char user_uuid[MAX_UUID_LENGTH] = {0};
    char* first_quote = strchr(*users_start, '\"');
    char* second_quote = first_quote ? strchr(first_quote + 1, '\"') : NULL;
    if (first_quote && second_quote) {
        size_t uuid_len = second_quote - first_quote - 1;
        if (uuid_len != (MAX_UUID_LENGTH - 1)) {
            fprintf(stderr, "Error: UUID too long, skipping...\n");
            *users_start = second_quote + 1;
            return true;
        }
        strncpy(user_uuid, first_quote + 1, second_quote - first_quote - 1);
        strcpy(current_channel->users[*user_count], user_uuid);
        (*user_count)++;
        *users_start = second_quote + 1;
        return true;
    }
    return false;
}

static bool channel_users_parsing(channel_t* current_channel, char* json)
{
    char users_key[] = "\"users\": [";
    char* users_start = strstr(json, users_key);
    if (!users_start)
        return false;
    users_start += strlen(users_key);
    char* users_end = strchr(users_start, ']');
    if (!users_end)
        return false;

    int user_count = 0;
    while (users_start < users_end) {
        bool found_uuid = parse_user_uuid_in_channel(
            current_channel, &user_count, &users_start);
        if (!found_uuid) {
            break;
        }
    }
    current_channel->nb_users = user_count;
    return true;
}

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
    if (!channel_users_parsing(*current_channel, ptr)) return false;
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
