/*
** EPITECH PROJECT, 2022
** MyTeams
** File description:
** save_users.c
*/

#include "../../include/server.h"

void save_users_to_file(database_t* db)
{
    FILE* file = open_file("libs/database/users.json", "w");
    if (!file) return;

    fprintf(file, "[\n");
    user_t* user;
    bool first_user = true;

    LIST_FOREACH(user, &db->users, entries) {
        if (!first_user)
            fprintf(file, ",\n");

        first_user = false;
        fprintf(file, "  {\n");
        fprintf(file, "    \"uuid\": \"%s\",\n", user->uuid);
        fprintf(file, "    \"username\": \"%s\"\n", user->username);
        fprintf(file, "  }");
    }
    fprintf(file, "\n]\n");
    fclose(file);
}
