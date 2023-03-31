/*
** EPITECH PROJECT, 2022
** B-NWP-400-LYN-4-1-myteams-jules.dutel
** File description:
** info_team.c
*/

#include "../../include/client.h"

void info_team(char* json_response)
{
    char *team_uuid = json_get_value(json_response, "team_uuid");
    char *team_name = json_get_value(json_response, "team_name");
    char *team_description = json_get_value(json_response, "team_description");

    if (team_uuid == NULL || team_name == NULL || team_description == NULL) {
        printf("Error: Failed to get team information\n");
        return;
    }

    client_print_team(team_uuid, team_name, team_description);

    free(team_uuid);
    free(team_name);
    free(team_description);
}
