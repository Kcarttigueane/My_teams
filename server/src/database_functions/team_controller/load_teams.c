/*
** EPITECH PROJECT, 2022
** MyTeams
** File description:
** load_teams.c
*/

#include "../../../include/server.h"

static team_t* create_new_team(database_t* db, int* user_index,
team_t** current_team)
{
    *current_team = (team_t*)calloc(1, sizeof(team_t));
    LIST_INSERT_HEAD(&db->teams, *current_team, entries);
    *user_index = -1;
    return *current_team;
}

void handle_users_line(team_t* current_team, char* line, int* user_index)
{
    char value[256] = {0};
    sscanf(line, " \"%[^\"]\"", value);
    *user_index = *user_index + 1;
    strcpy(current_team->users[*user_index], value);
}

void handle_team_line(team_t* current_team, char* line)
{
    char key[64] = {0}, value[256] = {0};
    sscanf(line, " \"%[^\"]\": \"%[^\"]\"", key, value);

    (!strcmp(key, "uuid")) ? strcpy(current_team->uuid, value) : 0;
    (!strcmp(key, "name")) ? strcpy(current_team->name, value) : 0;
    (!strcmp(key, "description")) ? strcpy(current_team->description, value)
    : 0;
    (!strcmp(key, "users_count")) ? current_team->users_count = atoi(value) : 0;
    (!strcmp(key, "created_at")) ? current_team->created_at = atol(value) : 0;
}

void load_teams_from_file(database_t* db)
{
    FILE* file = fopen("libs/database/teams.json", "r");
    if (!file) return;

    char line[256] = {0};
    team_t* current_team = NULL;
    int user_index = -1;

    LIST_INIT(&db->teams);

    while (fgets(line, sizeof(line), file)) {

        (strstr(line, "{")) ? create_new_team(db, &user_index, &current_team)
        : (strstr(line, "}")) ? current_team = NULL
        : (current_team) ? handle_team_line(current_team, line)
        : (strstr(line, "\"") && current_team)
        ? handle_users_line(current_team, line, &user_index)
        : 0;
    }
    fclose(file);
}
