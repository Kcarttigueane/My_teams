/*
** EPITECH PROJECT, 2022
** B-NWP-400-LYN-4-1-myteams-jules.dutel
** File description:
** is_user_in_team.c
*/

#include "../../../include/server.h"

bool is_user_in_team(team_t* new_team, char* user_uuid)
{
    for (int i = 0; i < new_team->users_count; i++)
        if (!strcmp(new_team->users[i], user_uuid))
            return (true);
    return (false);
}
