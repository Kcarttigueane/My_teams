/*
** EPITECH PROJECT, 2022
** B-NWP-400-LYN-4-1-myteams-jules.dutel
** File description:
** print_teams.c
*/

#include "../../include/client.h"

void print_teams(char* json_response)
{
    char* ptr = strstr(json_response, "\"teams\": [");
    if (ptr == NULL) {
        printf("Error: teams not found\n");
        return;
    }
    ptr += strlen("\"teams\": [");
    while (ptr != NULL && *ptr != ']') {
        if (*ptr == ',') ptr++;
        char team_uuid[MAX_UUID_LENGTH] = {0};
        char team_name[MAX_NAME_LENGTH] = {0};
        char team_description[MAX_DESCRIPTION_LENGTH] = {0};
        if (!extract_value("team_uuid", ptr, team_uuid, sizeof(team_uuid)))
            break;
        if (!extract_value("team_name", ptr, team_name, sizeof(team_name)))
            break;
        if (!extract_value("team_description", ptr, team_description,
            sizeof(team_description))) break;
        client_print_teams(team_uuid, team_name, team_description);
        ptr = strstr(ptr, "},");
        if (ptr != NULL) ptr += 2;
    }
}
