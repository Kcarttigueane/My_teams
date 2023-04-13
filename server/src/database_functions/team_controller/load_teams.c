/*
** EPITECH PROJECT, 2022
** MyTeams
** File description:
** load_teams.c
*/

#include "../../../include/server.h"

static bool parse_user_uuid(team_t* current_team, int* user_count,
char** users_start)
{
    char user_uuid[MAX_UUID_LENGTH] = {0};
    char* first_quote = strchr(*users_start, '\"');
    char* second_quote = first_quote ? strchr(first_quote + 1, '\"') : NULL;
    if (first_quote && second_quote) {
        size_t uuid_len = second_quote - first_quote - 1;
        if (uuid_len != (MAX_UUID_LENGTH - 1)) {
            fprintf(stdout, "Error: UUID too long, skipping...\n");
            *users_start = second_quote + 1;
            return true;
        }
        strncpy(user_uuid, first_quote + 1, uuid_len);
        user_uuid[uuid_len] = '\0';
        strcpy(current_team->users[*user_count], user_uuid);
        (*user_count)++;
        *users_start = second_quote + 1;
        return true;
    }
    return false;
}

static bool team_users_parsing(team_t* current_team, char* json)
{
    char users_key[] = "\"users\": [";
    char* users_start = strstr(json, users_key);
    if (!users_start) return false;
    users_start += strlen(users_key);
    char* users_end = strchr(users_start, ']');
    if (!users_end) return false;

    int user_count = 0;
    while (users_start < users_end) {
        bool found_uuid =
            parse_user_uuid(current_team, &user_count, &users_start);
        if (!found_uuid) break;
    }
    current_team->users_count = user_count;
    return true;
}

static bool team_parsing(database_t* db, char* ptr, team_t** current_team)
{
    *current_team = calloc(1, sizeof(team_t));
    if (!*current_team)
        return false;

    char timestamp[MAX_TIMESTAMP_LENGTH] = {0};
    extract_value("uuid", ptr, (*current_team)->uuid, MAX_UUID_LENGTH);
    extract_value("name", ptr, (*current_team)->name, MAX_NAME_LENGTH);
    extract_value("description", ptr, (*current_team)->description,
    MAX_DESCRIPTION_LENGTH);
    extract_value("created_at", ptr, timestamp, MAX_TIMESTAMP_LENGTH);
    (*current_team)->created_at = string_to_timestamp(timestamp);

    if (!team_users_parsing(*current_team, ptr))
        return false;

    debug_team(*current_team);

    LIST_INSERT_HEAD(&db->teams, *current_team, entries);

    return true;
}

bool parse_teams_json(database_t* db, char* json)
{
    LIST_INIT(&db->teams);

    char* ptr = strstr(json, "[");

    ptr += strlen("[");

    team_t* current_team = NULL;

    while (ptr != NULL && *ptr != ']') {
        if (*ptr == ',')
            ptr++;
        if (!team_parsing(db, ptr, &current_team))
            return false;
        ptr = strstr(ptr, "},");
        if (ptr != NULL)
            ptr += 2;
    }

    return true;
}

void load_teams_from_file(database_t* db)
{
    FILE* file = open_file("libs/database/teams.json", "r");
    if (!file) return;

    char* buffer = read_file_contents(file);

    if (!buffer) {
        fclose(file);
        return;
    }

    bool success = parse_teams_json(db, buffer);

    if (!success) {
        fclose(file);
        free(buffer);
        return;
    }

    fclose(file);
    free(buffer);
}
