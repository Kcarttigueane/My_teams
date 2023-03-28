/*
** EPITECH PROJECT, 2022
** B-NWP-400-LYN-4-1-myteams-jules.dutel
** File description:
** free_teams.c
*/

#include "../../../include/server.h"

void free_teams(database_t* db)
{
    team_t* team;
    team_t* tmp;

    LIST_FOREACH_SAFE(team, &(db->teams), entries, tmp) {
        LIST_REMOVE(team, entries);
        free(team);
    }
}
