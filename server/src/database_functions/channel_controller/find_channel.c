/*
** EPITECH PROJECT, 2022
** B-NWP-400-LYN-4-1-myteams-jules.dutel
** File description:
** find_channel.c
*/

#include "../../../include/server.h"

channel_t* find_channel_by_uuid(database_t* db, char* channel_uuid)
{
    channel_t* channel;

    LIST_FOREACH(channel, &(db->channels), entries) {
        if (!strcmp(channel->uuid, channel_uuid))
            return channel;
    }
    printf("Error: Channel not found\n");
    return NULL;
}

bool is_channel_already_exist(database_t* db, char* channel_name)
{
    channel_t* channel;

    LIST_FOREACH(channel, &(db->channels), entries) {
        if (!strcmp(channel->name, channel_name))
            return true;
    }
    return false;
}
