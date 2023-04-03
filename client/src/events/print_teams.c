/*
** EPITECH PROJECT, 2022
** B-NWP-400-LYN-4-1-myteams-jules.dutel
** File description:
** print_teams.c
*/

#include "../../include/client.h"

bool is_team_info_valid(char* team_uuid, char* team_name,
char* team_description)
{
    return *team_uuid != '\0' && *team_name != '\0' &&
    *team_description != '\0';
}

static bool team_parsing(char* ptr)
{
    char team_uuid[MAX_UUID_LENGTH] = {0};
    char team_name[MAX_NAME_LENGTH] = {0};
    char team_description[MAX_DESCRIPTION_LENGTH] = {0};

    extract_value("team_uuid", ptr, team_uuid, MAX_UUID_LENGTH);
    extract_value("team_name", ptr, team_name, MAX_NAME_LENGTH);
    extract_value("team_description", ptr, team_description,
    MAX_DESCRIPTION_LENGTH);

    if (!is_team_info_valid(team_uuid, team_name, team_description))
        return false;

    client_print_teams(team_uuid, team_name, team_description);

    return true;
}

void print_teams(char* json_response)
{
    char* ptr = strstr(json_response, "\"teams\": [");
    if (ptr == NULL) {
        printf("Error: teams not found\n");
        return;
    }
    ptr += strlen("\"teams\": [");
    while (ptr != NULL && *ptr != ']') {
        if (*ptr == ',')
            ptr++;
        if (!team_parsing(ptr))
            break;
        ptr = strstr(ptr, "},");
        if (ptr != NULL)
            ptr += 2;
    }
}
