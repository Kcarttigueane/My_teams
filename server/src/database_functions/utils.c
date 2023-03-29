/*
** EPITECH PROJECT, 2022
** B-NWP-400-LYN-4-1-myteams-jules.dutel
** File description:
** utils.c
*/

#include "../../include/server.h"

bool is_channel_related_to_team(team_t* team, channel_t* channel)
{
    return channel && team && !strcmp(channel->team_uuid, team->uuid);
}

bool is_thread_related_to_channel_to_team(team_t* team, channel_t* channel,
thread_t* thread)
{
    return thread && is_channel_related_to_team(team, channel) &&
    !strcmp(thread->related_channel_uuid, channel->uuid);
}
