/*
** EPITECH PROJECT, 2022
** MyTeams
** File description:
** save_load_users.c
*/

#include "../../../include/server.h"

static bool users_parsing(database_t *db, char* ptr)
{
    user_t* current_user = calloc(1, sizeof(user_t));
    if (!current_user) return false;

    char uuid[MAX_UUID_LENGTH] = {0};
    char username[MAX_NAME_LENGTH] = {0};

    extract_value("uuid", ptr, uuid, MAX_UUID_LENGTH);
    extract_value("username", ptr, username, MAX_NAME_LENGTH);

    strcpy(current_user->uuid, uuid);
    strcpy(current_user->username, username);

    LIST_INSERT_HEAD(&db->users, current_user, entries);

    server_event_user_loaded(current_user->uuid, current_user->username);

    return true;
}

bool parse_users_json(database_t* db, const char* json)
{
    LIST_INIT(&db->users);

    char* ptr = strstr(json, "[");

    ptr += strlen("[");

    while (ptr != NULL && *ptr != ']') {
        if (*ptr == ',') ptr++;
        if (!users_parsing(db, ptr))
            return false;
        ptr = strstr(ptr, "},");
        if (ptr != NULL) ptr += 2;
    }

    return true;
}

void load_users_from_file(database_t* db)
{
    FILE* file = open_file("libs/database/users.json", "r");
    if (!file) return;

    char* buffer = read_file_contents(file);

    if (!buffer) {
        fclose(file);
        return;
    }

    bool success = parse_users_json(db, buffer);

    if (!success) {
        fclose(file);
        free(buffer);
        return;
    }

    fclose(file);
    free(buffer);
}
