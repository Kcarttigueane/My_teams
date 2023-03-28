/*
** EPITECH PROJECT, 2022
** B-NWP-400-LYN-4-1-myteams-jules.dutel
** File description:
** list_teams.c
*/

#include "../../../include/server.h"

void list_teams(database_t* db)
{
    team_t* team;

    printf("Teams in the database:\n");

    LIST_FOREACH(team, &(db->teams), entries) {
        printf("- Name: %s\n", team->name);
        printf("  Description: %s\n", team->description);
        printf("  Users:\n");
        printf("  Current Unix timestamp: %ld\n", (long)team->created_at);

        for (int i = 0; i < team->users_count; i++) {
            printf("    - %s\n", team->users[i]);
        }
    }
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
    printf("Team created at: %ld\n", (long)team->created_at);
    printf("Team users:\n");

    for (int i = 0; i < team->users_count; i++)
        printf("- %s\n", team->users[i]);
}
