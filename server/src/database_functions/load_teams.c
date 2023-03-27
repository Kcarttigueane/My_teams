/*
** EPITECH PROJECT, 2022
** MyTeams
** File description:
** load_teams.c
*/

#include "../../include/server.h"

void load_teams_from_file(database_t* db)
{
    FILE* file = fopen("libs/database/teams.json", "r");
    if (!file)
        return;

    char line[256];
    team_t* current_team = NULL;
    int user_index = -1;

    LIST_INIT(&db->teams);

    while (fgets(line, sizeof(line), file)) {
        if (strstr(line, "{")) {
            current_team = malloc(sizeof(team_t));
            LIST_INSERT_HEAD(&db->teams, current_team, entries);
            user_index = -1;
        } else if (strstr(line, "}")) {
            current_team = NULL;
        } else if (current_team) {
            char key[64], value[256];
            sscanf(line, " \"%[^\"]\": \"%[^\"]\"", key, value);

            if (strcmp(key, "uuid") == 0) {
                strcpy(current_team->uuid, value);
            } else if (strcmp(key, "name") == 0) {
                strcpy(current_team->name, value);
            } else if (strcmp(key, "description") == 0) {
                strcpy(current_team->description, value);
            } else if (strcmp(key, "users_count") == 0) {
                current_team->users_count = atoi(value);
            }
        } else if (strstr(line, "\"") && current_team) {
            char value[256];
            sscanf(line, " \"%[^\"]\"", value);
            user_index++;
            strcpy(current_team->users[user_index], value);
        }
    }

    fclose(file);
}
