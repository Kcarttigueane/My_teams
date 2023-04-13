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
    printf("\t\t[Created at] %s\n", created_at);
    printf(RESET);

    free(created_at);
}
