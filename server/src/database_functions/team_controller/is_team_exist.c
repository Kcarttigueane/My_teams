/*
** EPITECH PROJECT, 2022
** B-NWP-400-LYN-4-1-myteams-jules.dutel
** File description:
** is_team_exist.c
*/

#include "../../../include/server.h"

bool is_team_exists(database_t* db, char* team_uuid)
{
    team_t* team;

    LIST_FOREACH(team, &(db->teams), entries) {
        if (!strcmp(team->uuid, team_uuid))
            return true;
    }

    return false;
}
