/*
** EPITECH PROJECT, 2022
** B-NWP-400-LYN-4-1-myteams-jules.dutel
** File description:
** unsubscribed_from_team.c
*/

#include "../../include/client.h"

void unsubscribed_from_team(char* json_response)
{
    char *user_uuid = json_get_value(json_response, "user_uuid");
    char *team_uuid = json_get_value(json_response, "team_uuid");

    if (user_uuid == NULL || team_uuid == NULL) {
        printf("Error: invalid JSON format\n");
        return;
    }

    client_print_unsubscribed(user_uuid, team_uuid);

    free(user_uuid);
    free(team_uuid);
}
