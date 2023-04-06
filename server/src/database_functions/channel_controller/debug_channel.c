/*
** EPITECH PROJECT, 2022
** B-NWP-400-LYN-4-1-myteams-jules.dutel
** File description:
** debug_channel.c
*/

#include "../../../../include/color.h"
#include "../../../include/server.h"

void debug_channel(channel_t* new_channel)
{
    char *created_at = timestamp_to_string(new_channel->created_at);

    printf(RED);
    printf("[Channel] %s\n", CLIENT_PROMPT);
    printf(PURPLE);
    printf("\t\t[UUID] %s\n", new_channel->uuid);
    printf("\t\t[Name] %s\n", new_channel->name);
    printf("\t\t[Description] %s\n", new_channel->description);
    printf("\t\t[Team UUID] %s\n", new_channel->team_uuid);
    printf("\t\t[Creator UUID] %s\n", new_channel->creator_uuid);
    printf("\t\t[nb_users] %zu\n", new_channel->nb_users);
    printf("\t\t[Created at] %s\n", created_at);
    printf("\t\t[Users] \n");

    for (size_t i = 0; i < new_channel->nb_users; i++)
        printf("    \t\t\t- %s\n", new_channel->users[i]);

    printf("\n");
    printf(RESET);
}
