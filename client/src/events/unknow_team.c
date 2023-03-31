/*
** EPITECH PROJECT, 2022
** B-NWP-400-LYN-4-1-myteams-jules.dutel
** File description:
** unknow_team.c
*/

#include "../../include/client.h"

void unknow_team(char* json_response)
{
    char *team_uuid = json_get_value(json_response, "team_uuid");

    if (team_uuid == NULL) {
        printf("Error: invalid JSON format\n");
        return;
    }

    client_error_unknown_team(team_uuid);

    free(team_uuid);
}
