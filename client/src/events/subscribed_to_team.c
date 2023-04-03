/*
** EPITECH PROJECT, 2022
** B-NWP-400-LYN-4-1-myteams-jules.dutel
** File description:
** subscribed_to_team.c
*/

#include "../../include/client.h"

void subscribed_to_team(char* json_response)
{
    char user_uuid[MAX_UUID_LENGTH] = {0};
    char team_uuid[MAX_UUID_LENGTH] = {0};

    if (!extract_value("user_uuid", json_response, user_uuid,
        sizeof(user_uuid)) ||
        !extract_value("team_uuid", json_response, team_uuid,
        sizeof(team_uuid))) {
        printf("Error: invalid JSON format\n");
        return;
    }

    client_print_subscribed(user_uuid, team_uuid);
}
