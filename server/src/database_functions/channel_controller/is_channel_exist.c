/*
** EPITECH PROJECT, 2022
** B-NWP-400-LYN-4-1-myteams-jules.dutel
** File description:
** is_channel_exist.c
*/

#include "../../../include/server.h"

bool is_channel_exist(database_t* db, char* team_uuid)
{
    channel_t* channel;

    LIST_FOREACH(channel, &(db->channels), entries) {
        if (!strcmp(channel->team_uuid, team_uuid))
            return true;
    }

    return false;
}
