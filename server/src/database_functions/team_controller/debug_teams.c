/*
** EPITECH PROJECT, 2022
** B-NWP-400-LYN-4-1-myteams-jules.dutel
** File description:
** debug_teams.c
*/

#include "../../../include/server.h"
#include "../../../../include/color.h"

void debug_team(team_t* new_team)
{
    char *created_at = timestamp_to_string(new_team->created_at);

    printf(GREEN);
    printf("[Team created] %s\n", CLIENT_PROMPT);
    printf(PURPLE);
    printf("\t\t[UUID] %s\n", new_team->uuid);
    printf("\t\t[Name] %s\n", new_team->name);
    printf("\t\t[Description] %s\n", new_team->description);
    printf("\t\t[Users count] %d\n", new_team->users_count);
    printf("\t\t[Created at] %s\n", created_at);

    free(created_at);

    for (int i = 0; i < new_team->users_count; i++)
        printf("    \t\t\t- %s\n", new_team->users[i]);

    printf("\n");
    printf(RESET);
}
