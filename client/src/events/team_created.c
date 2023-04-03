/*
** EPITECH PROJECT, 2022
** B-NWP-400-LYN-4-1-myteams-jules.dutel
** File description:
** team_created.c
*/

#include "../../include/client.h"

void team_created(char* json_response)
{
    char team_uuid[MAX_UUID_LENGTH] = {0};
    char team_name[MAX_NAME_LENGTH] = {0};
    char team_description[MAX_DESCRIPTION_LENGTH] = {0};

    if (!extract_value("team_uuid", json_response, team_uuid,
        sizeof(team_uuid)) ||
        !extract_value("team_name", json_response, team_name,
        sizeof(team_name)) ||
        !extract_value("team_description", json_response, team_description,
        sizeof(team_description))) {
        printf("Error: invalid JSON format\n");
        return;
    }

    client_event_team_created(team_uuid, team_name, team_description);
}
