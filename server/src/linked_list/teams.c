/*
** EPITECH PROJECT, 2022
** MyTeams
** File description:
** teams.c
*/

#include "../../include/server.h"

team_t* create_team(database_t* db, char* name, char* description)
{
    team_t* new_team = malloc(sizeof(team_t));

    if (new_team == NULL) {
        printf("Error: Failed to allocate memory for new team\n");
        return NULL;
    }

    char *team_uuid = generate_uuid();
    strncpy(new_team->uuid, team_uuid, MAX_UUID_STR_LEN);
    strncpy(new_team->name, name, MAX_NAME_LENGTH);
    strncpy(new_team->description, description, MAX_DESCRIPTION_LENGTH);
    new_team->users_count = 0;
    free(team_uuid);

    LIST_INSERT_HEAD(&(db->teams), new_team, entries);

    return new_team;
}

void list_teams(database_t* db)
{
    team_t* team;

    printf("Teams in the database:\n");

    LIST_FOREACH(team, &(db->teams), entries) {
        printf("- Name: %s\n", team->name);
        printf("  Description: %s\n", team->description);
        printf("  Users:\n");

        for (int i = 0; i < team->users_count; i++) {
            printf("    - %s\n", team->users[i]);
        }
    }
}

void free_teams(database_t* db)
{
    team_t* team;
    team_t *tmp;

    LIST_FOREACH_SAFE(team, &(db->teams), entries, tmp) {
        LIST_REMOVE(team, entries);
        free(team);
    }
}

bool is_team_exists(database_t* db, char* team_uuid)
{
    team_t* team;

    LIST_FOREACH(team, &(db->teams), entries) {
        if (!strcmp(team->uuid, team_uuid))
            return true;
    }

    return false;
}

void display_team_info(database_t* db, char* team_uuid)
{
    team_t* team = NULL;

    LIST_FOREACH(team, &(db->teams), entries) {
        if (!strcmp(team->uuid, team_uuid))
            break;
    }

    if (team == NULL) {
        printf("Error: Team not found\n");
        return;
    }

    printf("Team UUID: %s\n", team->uuid);
    printf("Team name: %s\n", team->name);
    printf("Team description: %s\n", team->description);
    printf("Team users:\n");

    for (int i = 0; i < team->users_count; i++)
        printf("- %s\n", team->users[i]);
}
