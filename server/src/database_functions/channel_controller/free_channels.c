/*
** EPITECH PROJECT, 2022
** B-NWP-400-LYN-4-1-myteams-jules.dutel
** File description:
** free_channels.c
*/

#include "../../../include/server.h"

void free_channels(database_t* db)
{
    channel_t* channel;
    channel_t* tmp;

    LIST_FOREACH_SAFE(channel, &db->channels, entries, tmp) {
        LIST_REMOVE(channel, entries);
        free(channel);
    }
}
