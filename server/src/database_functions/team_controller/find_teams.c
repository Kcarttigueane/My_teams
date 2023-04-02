/*
** EPITECH PROJECT, 2022
** B-NWP-400-LYN-4-1-myteams-jules.dutel
** File description:
** find_teams.c
*/

#include "../../../include/server.h"

team_t* find_team_by_uuid(database_t* db, char* team_uuid)
{
    team_t* team = NULL;

    LIST_FOREACH(team, &(db->teams), entries) {
        if (!strcmp(team->uuid, team_uuid))
            return team;
    }
    printf("Error: Team not found\n");
    return NULL;
}

bool is_team_already_exist(database_t* db, char* team_name)
{
    team_t* team = NULL;

    LIST_FOREACH(team, &(db->teams), entries) {
        if (!strcmp(team->name, team_name))
            return true;
    }
    return false;
}
