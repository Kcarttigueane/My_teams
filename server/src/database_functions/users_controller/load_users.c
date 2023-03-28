/*
** EPITECH PROJECT, 2022
** MyTeams
** File description:
** save_load_users.c
*/

#include "../../../include/server.h"

static user_t* create_new_user(database_t* db)
{
    user_t* user = (user_t*)malloc(sizeof(user_t));
    LIST_INSERT_HEAD(&db->users, user, entries);
    return user;
}

static void set_user_field(user_t* user, char* line)
{
    char key[64], value[64];
    sscanf(line, " \"%[^\"]\": \"%[^\"]\"", key, value);

    if (!strcmp(key, "uuid")) {
        strcpy(user->uuid, value);
    } else if (!strcmp(key, "username")) {
        strcpy(user->username, value);
    }
}

void load_users_from_file(database_t* db)
{
    FILE* file = open_file("libs/database/users.json", "r");

    if (!file) return;

    LIST_INIT(&db->users);

    char line[256];
    user_t* current_user = NULL;

    while (fgets(line, sizeof(line), file)) {
        is_start_json(line) ? current_user = create_new_user(db)
        : is_end_json(line) ? current_user = NULL
        : current_user ? set_user_field(current_user, line)
        : (void)0;
    }

    fclose(file);
}
